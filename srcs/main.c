/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/28 12:26:57 by ametapod          #+#    #+#             */
/*   Updated: 2020/10/02 16:37:43 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void		my_loop(t_vars *vars)
{
	vars->win = mlx_new_window(vars->mlx, vars->d_width, vars->d_height,
																	"cub3D");
	mlx_hook(vars->win, 2, (1L << 0), key_press_hook, vars);
	mlx_hook(vars->win, 3, (1L << 1), key_release_hook, vars);
	mlx_hook(vars->win, 17, (1L << 17), exit_hook, vars);
	mlx_loop_hook(vars->mlx, render_next_frame, vars);
	mlx_loop(vars->mlx);
}

int				main(int argc, char **argv)
{
	t_vars	vars;
	t_img	img;
	t_pos	pos;

	vars.img = &img;
	vars.pos = &pos;
	if (!check_args(argc, argv))
		return (error_msg("Wrong parameters!\n"));
	vars.mlx = mlx_init();
	mlx_get_screen_size(vars.mlx, &vars.d_width, &vars.d_height);
	if (!read_file(argv[1], &vars) || !vars_setup(&vars))
		return (0);
	if (!(img.img = mlx_new_image(vars.mlx, vars.d_width, vars.d_height)))
		return (free_app(&vars, 1, 0));
	img.addr = mlx_get_data_addr(img.img, &img.bps,
									&img.line_len, &img.endian);
	if (argc == 3)
		return (free_app(&vars, 1, 0));
	else
		my_loop(&vars);
	return (1);
}
