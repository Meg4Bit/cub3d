/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:26:57 by ametapod          #+#    #+#             */
/*   Updated: 2020/09/29 12:15:25 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void            verLine(t_vars *vars, t_img *img, int x, t_ray ray)
{
	int		texX;
	int		texY;
	double	step;
	double	texPos;
	int		y;

	texX = (int)(ray.wallx * (double)img->width);
	if((ray.side == 0 && ray.dirx > 0) || (ray.side == 1 && ray.diry < 0))
		texX = img->width - texX - 1;
	step = 1.0 * img->height / ray.line_height;
	texPos = (ray.draw_start - vars->d_height / 2 + ray.line_height / 2) * step;
	y = 0;
	while (y < ray.draw_start)
		my_mlx_pixel_put(vars->img, x, y++, vars->floor_color);
	while (y < ray.draw_end)
	{
		texY = (int)texPos & (img->height - 1);
		texPos += step;
		my_mlx_pixel_put(vars->img, x, y++, *(unsigned int *)(img->addr +
					(texY * img->line_len + texX * (img->bps / 8))));
	}
	while (y < vars->d_height)
		my_mlx_pixel_put(vars->img, x, y++, vars->ceil_color);
}

void           load_textures(t_vars *vars)
{
	int i;

	i = -1;
	vars->tex[0].img = mlx_xpm_file_to_image(vars->mlx, "./cub_textures/13.xpm", &vars->tex[0].width, &vars->tex[0].height);
	vars->tex[1].img = mlx_xpm_file_to_image(vars->mlx, "./cub_textures/14.xpm", &vars->tex[1].width, &vars->tex[1].height);
	vars->tex[2].img = mlx_xpm_file_to_image(vars->mlx, "./cub_textures/26.xpm", &vars->tex[2].width, &vars->tex[2].height);
	vars->tex[3].img = mlx_xpm_file_to_image(vars->mlx, "./cub_textures/17.xpm", &vars->tex[3].width, &vars->tex[3].height);
	vars->tex[4].img = mlx_xpm_file_to_image(vars->mlx, "./cub_textures/sprite.xpm", &vars->tex[4].width, &vars->tex[4].height);
	while (++i < 5)
		vars->tex[i].addr = mlx_get_data_addr(vars->tex[i].img, &vars->tex[i].bps, &vars->tex[i].line_len,
                                 &vars->tex[i].endian);
}

void			move_body(t_pos *pos)
{
	double old_dirx;
	double old_planex;
	double norm_planex;
	double norm_planey;

	norm_planex = 1 / 0.66 * pos->planex;
	norm_planey = 1 / 0.66 * pos->planey;
	if(!worldMap[(int)(pos->x + pos->dirx * pos->move_speed)][(int)(pos->y)])
		pos->x += pos->dirx * pos->move_speed;
	if(!worldMap[(int)(pos->x)][(int)(pos->y + pos->diry * pos->move_speed)])
		pos->y += pos->diry * pos->move_speed;
	if(!worldMap[(int)(pos->x + norm_planex * pos->move_hor)][(int)(pos->y)])
		pos->x += norm_planex * pos->move_hor;
	if(!worldMap[(int)(pos->x)][(int)(pos->y + norm_planey * pos->move_hor)])
		pos->y += norm_planey * pos->move_hor;
	old_dirx = pos->dirx;
	pos->dirx = pos->dirx * cos(pos->rot_speed) - pos->diry
						* sin(pos->rot_speed);
	pos->diry = old_dirx * sin(pos->rot_speed) + pos->diry * cos(pos->rot_speed);
	old_planex = pos->planex;
	pos->planex = pos->planex * cos(pos->rot_speed) - pos->planey
						* sin(pos->rot_speed);
	pos->planey = old_planex * sin(pos->rot_speed) + pos->planey
						* cos(pos->rot_speed);
}

void			sort_sprites(t_sprite *sprites, double *dist, int amount)
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
void			draw_sprite(t_spRay *spr, t_vars *vars);

void			sprite_size(t_spRay *spr, t_vars *vars)
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

void			draw_sprite(t_spRay *spr, t_vars *vars)
{
	int				x;
	int				y;
	int				texX;
	int				texY;
	unsigned int	color;

	x = spr->draw_startx;
	while (x < spr->draw_endx)
	{
		y = spr->draw_starty - 1;
		texX = (int)(256 * (x - (-spr->width / 2 + spr->screenx))
					* vars->tex[4].width / spr->width) / 256;
		if (spr->transy > 0 && x > 0 && x < vars->d_width &&
						spr->transy < vars->pos->wall_buf[x])
			while (++y < spr->draw_endy)
			{
				texY = ((((y - spr->move_spr) * 256 - vars->d_height
	* 128 + spr->height * 128) * vars->tex[4].height) / spr->height) / 256;
				color = *(unsigned int *)(vars->tex[4].addr + (texY
	* vars->tex[4].line_len + texX * (vars->tex[4].bps / 8)));
				if (color != 0x00980088)
					my_mlx_pixel_put(vars->img, x, y, color);
			}
		x++;
	}
}

void			print_sprite(t_vars *vars, t_pos *pos)
{
	t_spRay		spr;
	double		invDet;
	double		sprX;
	double		sprY;
	int			i;

	i = 0;
	while (i < vars->num_spr)
	{
		pos->sprDist[i] = pow((pos->x - vars->spr[i].x), 2)
		+ pow((pos->y - vars->spr[i].y), 2);
		i++;
	}
	sort_sprites(vars->spr, pos->sprDist, vars->num_spr);
	i = 0;
	while (i < vars->num_spr)
	{
		sprX = vars->spr[i].x - pos->x;
		sprY = vars->spr[i++].y - pos->y;
		invDet = 1.0 / (pos->planex * pos->diry - pos->dirx * pos->planey);
		spr.transx = invDet * (pos->diry * sprX - pos->dirx * sprY);
		spr.transy = invDet * (-pos->planey * sprX + pos->planex * sprY);
		spr.screenx = (vars->d_width / 2) * (1 + spr.transx / spr.transy);
		sprite_size(&spr, vars);
	}
}

void			line_size(t_ray *ray, t_vars *vars)
{
	ray->line_height = (int)(vars->d_height / ray->perp2wall);
	ray->draw_start = -ray->line_height / 2 + vars->d_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + vars->d_height / 2;
	if (ray->draw_end >= vars->d_height)
		ray->draw_end = vars->d_height - 1;
	if (ray->side == 0)
		ray->wallx = vars->pos->y + ray->perp2wall * ray->diry;
	else
		ray->wallx = vars->pos->x + ray->perp2wall * ray->dirx;
	ray->wallx -= floor((ray->wallx));
}

void			dist2wall(t_ray *ray, t_pos *pos, int x, int y)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delt_distx;
			x += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->side_disty += ray->delt_disty;
			y += ray->stepy;
			ray->side = 1;
		}
		if (worldMap[x][y] > 0)
			hit = 1;
	}
	if (ray->side == 0)
		ray->perp2wall = (x - pos->x + (1 - ray->stepx) / 2) / ray->dirx;
	else
		ray->perp2wall = (y - pos->y + (1 - ray->stepy) / 2) / ray->diry;
}

void			ray_dda(t_ray *ray, t_vars *vars, int mapX, int mapY)
{
	if(ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->side_distx = (vars->pos->x - mapX) * ray->delt_distx;
	}
	else
	{
		ray->stepx = 1;
		ray->side_distx = (mapX + 1.0 - vars->pos->x) * ray->delt_distx;
	}
	if(ray->diry < 0)
	{
		ray->stepy = -1;
		ray->side_disty = (vars->pos->y - mapY) * ray->delt_disty;
	}
	else
	{
		ray->stepy = 1;
		ray->side_disty = (mapY + 1.0 - vars->pos->y) * ray->delt_disty;
	}
	dist2wall(ray, vars->pos, mapX, mapY);
	line_size(ray, vars);
}

t_ray			ray_casting(t_vars *vars, int x, t_img *img)
{
	t_ray	ray;
	int		mapX;
	int		mapY;

	ray.camerax = 2 * x / (double)vars->d_width - 1;
	ray.dirx = vars->pos->dirx + vars->pos->planex * ray.camerax;
	ray.diry = vars->pos->diry + vars->pos->planey * ray.camerax;
	mapX = vars->pos->x;
	mapY = vars->pos->y;
	ray.delt_distx = fabs(1 / ray.dirx);
	ray.delt_disty = fabs(1 / ray.diry);
	ray_dda(&ray, vars, mapX, mapY);
	if(!ray.side && ray.dirx > 0) *img = vars->tex[0];
	if(!ray.side && ray.dirx < 0) *img = vars->tex[1];
	if(ray.side && ray.diry > 0) *img = vars->tex[2];
	if(ray.side && ray.diry < 0) *img = vars->tex[3];
	return (ray);
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
		verLine(vars, &img, x, ray);
		vars->pos->wall_buf[x++] = ray.perp2wall;
	}
	print_sprite(vars, vars->pos);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	move_body(vars->pos);
	return (1);
}

int				exit_hook(int keycode)
{
	(void)keycode;
	exit (0);
}

int				free_app(t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	mlx_destroy_image(vars->mlx, vars->img->img);
	for (int i = 0; i < 5; i++)
		mlx_destroy_image(vars->mlx, vars->tex[i].img);
	free(vars->pos->wall_buf);
	mlx_destroy_window(vars->mlx, vars->win);
	free(vars->mlx);
	return (0);
}

int             key_press_hook(int keycode, t_vars *vars)
{
	if (keycode == 0xff53)
		vars->pos->rot_speed = -0.03;
	if (keycode == 0xff51)
		vars->pos->rot_speed = 0.03;
	if (keycode == 0x0077)
		vars->pos->move_speed = 0.05;
	if (keycode == 0x0073)
		vars->pos->move_speed = -0.05;
	if (keycode == 0x0061)
		vars->pos->move_hor = -0.05;
	if (keycode == 0x0064)
		vars->pos->move_hor = 0.05;
	if (keycode == 0xff1b)
		exit (free_app(vars));
	return (1);
}

int             key_release_hook(int keycode, t_vars *vars)
{
	if (keycode == 0xff53)
		vars->pos->rot_speed = 0;
	if (keycode == 0xff51)
		vars->pos->rot_speed = 0;
	if (keycode == 0x0077)
		vars->pos->move_speed = 0;
	if (keycode == 0x0073)
		vars->pos->move_speed = 0;
	if (keycode == 0x0061)
		vars->pos->move_hor = 0;
	if (keycode == 0x0064)
		vars->pos->move_hor = 0;
	return (1);
}

int             main(void)
{
    t_vars  vars;
    t_img   img;
    t_pos   pos;

    vars.d_width = 820;
    vars.d_height = 800;
	vars.ceil_color = create_rgb(220, 100, 0);
	vars.floor_color = create_rgb(225, 30, 0);
    pos.x = 22;
    pos.y = 12;
    pos.dirx = 0;
    pos.diry = -1;
    pos.planex = -0.66;
    pos.planey = 0;
	pos.rot_speed = 0;
	pos.move_speed = 0;
	pos.move_hor = 0;
	vars.num_spr = 2;
	vars.spr[0].x = 20;
	vars.spr[0].y = 10;
	vars.spr[1].x = 15;
	vars.spr[1].y = 10;
    /*double time = 0; //time of current frame
    double oldTime = 0; //time of previous frame*/

    vars.mlx = mlx_init();
	mlx_get_screen_size(vars.mlx, &vars.d_width, &vars.d_height);
    vars.win = mlx_new_window(vars.mlx, vars.d_width, vars.d_height, "cub3D");
    img.img = mlx_new_image(vars.mlx, vars.d_width, vars.d_height);
    img.addr = mlx_get_data_addr(img.img, &img.bps, &img.line_len,
                                 &img.endian);
    vars.img = &img;
    vars.pos = &pos;
	if (!(vars.pos->wall_buf = (double *)malloc(sizeof(double) * vars.d_width)))
		return (0);
	load_textures(&vars);
	mlx_hook(vars.win, 2, (1L<<0), key_press_hook, &vars);
	mlx_hook(vars.win, 3, (1L<<1), key_release_hook, &vars);
	mlx_hook(vars.win, 17, (1L<<17), exit_hook, 0);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
}