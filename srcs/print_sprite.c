/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:21:10 by ametapod          #+#    #+#             */
/*   Updated: 2020/10/02 15:20:38 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		sort_sprites(t_sprite *sprites, double *dist, int amount)
{
	int			i;
	int			j;
	t_sprite	tmp;

	i = 0;
	while (i < amount - 1)
	{
		j = 0;
		while (j < amount - i - 1)
		{
			if (dist[j] < dist[j + 1])
			{
				tmp = sprites[j];
				sprites[j] = sprites[j + 1];
				sprites[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void		draw_sprite(t_spray *spr, t_vars *vars)
{
	int				x;
	int				y;
	int				tex_x;
	int				tex_y;
	unsigned int	color;

	x = spr->draw_startx;
	while (x < spr->draw_endx)
	{
		y = spr->draw_starty - 1;
		tex_x = (int)(256 * (x - (-spr->width / 2 + spr->screenx))
					* vars->tex[4].width / spr->width) / 256;
		if (spr->transy > 0 && x > 0 && x < vars->d_width &&
						spr->transy < vars->pos->wall_buf[x])
			while (++y < spr->draw_endy)
			{
				tex_y = ((((y - spr->move_spr) * 256 - vars->d_height
	* 128 + spr->height * 128) * vars->tex[4].height) / spr->height) / 256;
				color = *(unsigned int *)(vars->tex[4].addr + (tex_y
	* vars->tex[4].line_len + tex_x * (vars->tex[4].bps / 8)));
				if (color != 0x00980088)
					my_mlx_pixel_put(vars->img, x, y, color);
			}
		x++;
	}
}

static void		sprite_size(t_spray *spr, t_vars *vars)
{
	spr->move_spr = (int)(77.0 / spr->transy);
	spr->height = abs((int)(vars->d_height / spr->transy));
	spr->draw_starty = -spr->height / 2 + vars->d_height / 2 + spr->move_spr;
	if (spr->draw_starty < 0)
		spr->draw_starty = 0;
	spr->draw_endy = spr->height / 2 + vars->d_height / 2 + spr->move_spr;
	if (spr->draw_endy >= vars->d_height)
		spr->draw_endy = vars->d_height - 1;
	spr->width = abs((int)(vars->d_height / (spr->transy)));
	spr->draw_startx = -spr->width / 2 + spr->screenx;
	if (spr->draw_startx < 0)
		spr->draw_startx = 0;
	spr->draw_endx = spr->width / 2 + spr->screenx;
	if (spr->draw_endx >= vars->d_width)
		spr->draw_endx = vars->d_width - 1;
	draw_sprite(spr, vars);
}

void			print_sprite(t_vars *vars, t_pos *pos)
{
	t_spray		spr;
	double		inv_det;
	double		spr_x;
	double		spr_y;
	int			i;

	i = 0;
	while (i < vars->num_spr)
	{
		pos->spr_dist[i] = pow((pos->x - vars->spr[i].x), 2)
		+ pow((pos->y - vars->spr[i].y), 2);
		i++;
	}
	sort_sprites(vars->spr, pos->spr_dist, vars->num_spr);
	i = 0;
	while (i < vars->num_spr)
	{
		spr_x = vars->spr[i].x - pos->x;
		spr_y = vars->spr[i++].y - pos->y;
		inv_det = 1.0 / (pos->planex * pos->diry - pos->dirx * pos->planey);
		spr.transx = inv_det * (pos->diry * spr_x - pos->dirx * spr_y);
		spr.transy = inv_det * (-pos->planey * spr_x + pos->planex * spr_y);
		spr.screenx = (vars->d_width / 2) * (1 + spr.transx / spr.transy);
		sprite_size(&spr, vars);
	}
}
