/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:20:59 by ametapod          #+#    #+#             */
/*   Updated: 2020/10/02 14:58:29 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		line_size(t_ray *ray, t_vars *vars)
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

static void		dist2wall(t_ray *ray, t_vars *vars, int x, int y)
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
		if (vars->map[x][y] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		ray->perp2wall = (x - vars->pos->x + (1 - ray->stepx) / 2) / ray->dirx;
	else
		ray->perp2wall = (y - vars->pos->y + (1 - ray->stepy) / 2) / ray->diry;
}

static void		ray_dda(t_ray *ray, t_vars *vars, int mapx, int mapy)
{
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->side_distx = (vars->pos->x - mapx) * ray->delt_distx;
	}
	else
	{
		ray->stepx = 1;
		ray->side_distx = (mapx + 1.0 - vars->pos->x) * ray->delt_distx;
	}
	if (ray->diry < 0)
	{
		ray->stepy = -1;
		ray->side_disty = (vars->pos->y - mapy) * ray->delt_disty;
	}
	else
	{
		ray->stepy = 1;
		ray->side_disty = (mapy + 1.0 - vars->pos->y) * ray->delt_disty;
	}
	dist2wall(ray, vars, mapx, mapy);
	line_size(ray, vars);
}

t_ray			ray_casting(t_vars *vars, int x, t_img *img)
{
	t_ray	ray;
	int		mapx;
	int		mapy;

	ray.camerax = 2 * x / (double)vars->d_width - 1;
	ray.dirx = vars->pos->dirx + vars->pos->planex * ray.camerax;
	ray.diry = vars->pos->diry + vars->pos->planey * ray.camerax;
	mapx = vars->pos->x;
	mapy = vars->pos->y;
	ray.delt_distx = fabs(1 / ray.dirx);
	ray.delt_disty = fabs(1 / ray.diry);
	ray_dda(&ray, vars, mapx, mapy);
	if (!ray.side && ray.dirx > 0)
		*img = vars->tex[0];
	if (!ray.side && ray.dirx < 0)
		*img = vars->tex[1];
	if (ray.side && ray.diry > 0)
		*img = vars->tex[2];
	if (ray.side && ray.diry < 0)
		*img = vars->tex[3];
	return (ray);
}
