/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:44:05 by ametapod          #+#    #+#             */
/*   Updated: 2020/10/02 16:41:04 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int				exit_hook(int keycode)
{
	(void)keycode;
	exit(0);
}

int				key_press_hook(int keycode, t_vars *vars)
{
	if (keycode == 0xff53)
		vars->pos->rot_speed = -0.03;
	if (keycode == 0xff51)
		vars->pos->rot_speed = 0.03;
	if (keycode == 0x0077)
		vars->pos->ms = 0.05;
	if (keycode == 0x0073)
		vars->pos->ms = -0.05;
	if (keycode == 0x0061)
		vars->pos->move_hor = -0.05;
	if (keycode == 0x0064)
		vars->pos->move_hor = 0.05;
	if (keycode == 0xff1b)
		free_app(vars, 1, 0);
	return (1);
}

int				key_release_hook(int keycode, t_vars *vars)
{
	if (keycode == 0xff53)
		vars->pos->rot_speed = 0;
	if (keycode == 0xff51)
		vars->pos->rot_speed = 0;
	if (keycode == 0x0077)
		vars->pos->ms = 0;
	if (keycode == 0x0073)
		vars->pos->ms = 0;
	if (keycode == 0x0061)
		vars->pos->move_hor = 0;
	if (keycode == 0x0064)
		vars->pos->move_hor = 0;
	return (1);
}
