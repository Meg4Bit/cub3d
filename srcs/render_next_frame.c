/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 13:26:33 by ametapod          #+#    #+#             */
/*   Updated: 2020/10/02 15:15:49 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		print_line(t_vars *vars, t_img *img, int x, t_ray ray)
{
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		y;

	tex_x = (int)(ray.wallx * (double)img->width);
	if ((ray.side == 0 && ray.dirx > 0) || (ray.side == 1 && ray.diry < 0))
		tex_x = img->width - tex_x - 1;
	step = 1.0 * img->height / ray.line_height;
	tex_pos = (ray.draw_start - vars->d_height / 2 + ray.line_height / 2)
					* step;
	y = 0;
	while (y < ray.draw_start)
		my_mlx_pixel_put(vars->img, x, y++, vars->floor_color);
	while (y < ray.draw_end)
	{
		tex_y = (int)tex_pos & (img->height - 1);
		tex_pos += step;
		my_mlx_pixel_put(vars->img, x, y++, *(unsigned int *)(img->addr +
					(tex_y * img->line_len + tex_x * (img->bps / 8))));
	}
	while (y < vars->d_height)
		my_mlx_pixel_put(vars->img, x, y++, vars->ceil_color);
}

static void		move_body(t_vars *vars, t_pos *pos)
{
	double old_dirx;
	double old_planex;
	double norm_x;
	double norm_y;

	norm_x = 1 / 0.66 * pos->planex;
	norm_y = 1 / 0.66 * pos->planey;
	if (vars->map[(int)(pos->x + pos->dirx * pos->ms)][(int)(pos->y)] != '1')
		pos->x += pos->dirx * pos->ms;
	if (vars->map[(int)(pos->x)][(int)(pos->y + pos->diry * pos->ms)] != '1')
		pos->y += pos->diry * pos->ms;
	if (vars->map[(int)(pos->x + norm_x * pos->move_hor)][(int)(pos->y)] != '1')
		pos->x += norm_x * pos->move_hor;
	if (vars->map[(int)(pos->x)][(int)(pos->y + norm_y * pos->move_hor)] != '1')
		pos->y += norm_y * pos->move_hor;
	old_dirx = pos->dirx;
	pos->dirx = pos->dirx * cos(pos->rot_speed) - pos->diry
						* sin(pos->rot_speed);
	pos->diry = old_dirx * sin(pos->rot_speed) + pos->diry
						* cos(pos->rot_speed);
	old_planex = pos->planex;
	pos->planex = pos->planex * cos(pos->rot_speed) - pos->planey
						* sin(pos->rot_speed);
	pos->planey = old_planex * sin(pos->rot_speed) + pos->planey
						* cos(pos->rot_speed);
}

int				render_next_frame(t_vars *vars)
{
	t_img	img;
	t_ray	ray;
	int		x;

	x = 0;
	while (x < vars->d_width)
		clear_img(vars->img, x++, 0, vars->d_height - 1);
	x = 0;
	while (x < vars->d_width)
	{
		ray = ray_casting(vars, x, &img);
		print_line(vars, &img, x, ray);
		vars->pos->wall_buf[x++] = ray.perp2wall;
	}
	if (vars->num_spr > 0)
		print_sprite(vars, vars->pos);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	move_body(vars, vars->pos);
	return (1);
}
