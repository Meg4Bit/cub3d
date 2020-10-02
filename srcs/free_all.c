/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 15:44:02 by ametapod          #+#    #+#             */
/*   Updated: 2020/10/02 16:34:57 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		free_win(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	if (vars->win)
	{
		mlx_clear_window(vars->mlx, vars->win);
		mlx_destroy_window(vars->mlx, vars->win);
	}
}

int				free_app(t_vars *vars, int flag, char *msg)
{
	int		i;

	i = 0;
	if (vars->map)
	{
		while (vars->map[i])
			free(vars->map[i++]);
		free(vars->map);
	}
	if (vars->pos->wall_buf)
		free(vars->pos->wall_buf);
	if (vars->pos->spr_dist)
		free(vars->pos->spr_dist);
	if (vars->num_spr != 0)
		if (vars->spr)
			free(vars->spr);
	i = 0;
	while (i < 5)
		mlx_destroy_image(vars->mlx, vars->tex[i++].img);
	flag == 1 ? free_win(vars) : 0;
	if (vars->mlx)
		free(vars->mlx);
	if (msg)
		return (error_msg(msg));
	exit(0);
}
