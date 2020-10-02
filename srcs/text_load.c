/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:58:43 by ametapod          #+#    #+#             */
/*   Updated: 2020/10/01 16:34:27 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int				load_textures(t_vars *vars, char *line, int *num)
{
	int i;

	if (*line == 'N' && *(line + 1) == 'O')
		i = 1;
	if (*line == 'S' && *(line + 1) == 'O')
		i = 0;
	if (*line == 'W' && *(line + 1) == 'E')
		i = 3;
	if (*line == 'E' && *(line + 1) == 'A')
		i = 2;
	if (*line == 'S' && *(line + 1) == ' ')
		i = 4;
	line += i == 4 ? 1 : 2;
	if (*line != ' ' || num[i + 1])
		return (error_msg("Wrong file information in textures"));
	while (*line == ' ')
		line++;
	if (!(vars->tex[i].img = mlx_xpm_file_to_image(vars->mlx,
			line, &vars->tex[i].width, &vars->tex[i].height)))
		return (error_msg("Wrong file path"));
	vars->tex[i].addr = mlx_get_data_addr(vars->tex[i].img,
	&vars->tex[i].bps, &vars->tex[i].line_len, &vars->tex[i].endian);
	num[i + 1] = 1;
	return (1);
}
