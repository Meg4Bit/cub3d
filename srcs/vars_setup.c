/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 23:04:00 by ametapod          #+#    #+#             */
/*   Updated: 2020/10/02 16:31:55 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		set_pos(t_vars *vars, char dir, int x, int y)
{
	vars->pos->x = x + 0.5;
	vars->pos->y = y + 0.5;
	if (dir == 'N' || dir == 's')
	{
		vars->pos->dirx = 1;
		vars->pos->diry = 0;
		vars->pos->planex = 0;
		vars->pos->planey = 0.66;
	}
	if (dir == 'N')
		vars->pos->dirx = -1;
	if (dir == 'S')
		vars->pos->planey = -0.66;
	if (dir == 'W' || dir == 'E')
	{
		vars->pos->dirx = 0;
		vars->pos->diry = -1;
		vars->pos->planex = 0.66;
		vars->pos->planey = 0;
	}
	if (dir == 'W')
		vars->pos->planex = -0.66;
	if (dir == 'E')
		vars->pos->diry = 1;
}

static int		map_check(t_vars *vars)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'S'
				|| vars->map[i][j] == 'W' || vars->map[i][j] == 'E')
			{
				set_pos(vars, vars->map[i][j], i, j);
				count++;
			}
			j++;
		}
		i++;
	}
	if (count != 1)
		return (0);
	return (1);
}

static int		set_sprites(t_vars *vars)
{
	int		i;
	int		j;
	int		count;

	if (!(vars->spr = (t_sprite *)malloc(sizeof(t_sprite) * vars->num_spr)))
		return (0);
	i = 0;
	count = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '2')
			{
				vars->spr[count].x = i + 0.5;
				vars->spr[count].y = j + 0.5;
				count++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

static int		count_sprites(t_vars *vars)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	count = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '2')
				count++;
			j++;
		}
		i++;
	}
	vars->num_spr = count;
	return (1);
}

int				vars_setup(t_vars *vars)
{
	vars->pos->rot_speed = 0;
	vars->pos->ms = 0;
	vars->pos->move_hor = 0;
	vars->num_spr = 0;
	vars->pos->spr_dist = 0;
	vars->pos->wall_buf = 0;
	vars->win = 0;
	if (!map_check(vars))
		return (free_app(vars, 0, "Invalid map"));
	count_sprites(vars);
	if (vars->num_spr > 0)
		if (!set_sprites(vars))
			return (free_app(vars, 0, "Malloc Error"));
	if (!(vars->pos->wall_buf = (double *)malloc(sizeof(double)
													* vars->d_width)))
		return (free_app(vars, 0, "Malloc Error"));
	if (vars->num_spr > 0)
		if (!(vars->pos->spr_dist = (double *)malloc(sizeof(double)
													* vars->num_spr)))
			return (free_app(vars, 0, "Malloc Error"));
	return (1);
}
