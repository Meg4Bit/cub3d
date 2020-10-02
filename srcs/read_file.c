/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 16:03:08 by ametapod          #+#    #+#             */
/*   Updated: 2020/10/02 15:42:16 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int		check_free(t_vars *vars, char *line, int *num, int fd)
{
	int		i;

	i = 1;
	while (i < 6)
	{
		if (num[i])
			mlx_destroy_image(vars->mlx, vars->tex[i - 1].img);
		i++;
	}
	free(vars->mlx);
	free(num);
	free(line);
	while (get_next_line(fd, &line))
		free(line);
	if (close(fd))
		return (error_msg("Close error"));
	return (0);
}

static int		floor_color(char *line, t_vars *vars, int *num)
{
	char	*begin;
	int		color[3];
	int		i;

	begin = line++;
	i = -1;
	while (*line == ' ')
		line++;
	while (++i < 3)
	{
		if (!ft_isdigit(*line) || (color[i] = ft_atoi(line)) < 0 ||
							color[i] > 255)
			return (error_msg("Wrong color"));
		while (ft_isdigit(*line))
			line++;
		if (*line != ',' && *line != 0)
			return (error_msg("Wrong color"));
		line += (*line == ',' && i < 2) ? 1 : 0;
	}
	if (*begin == 'F')
		vars->floor_color = create_rgb(color[0], color[1], color[2]);
	else
		vars->ceil_color = create_rgb(color[0], color[1], color[2]);
	i = *begin == 'F' ? 6 : 7;
	return (*line ? error_msg("Too many arguments in color") : (num[i] = 1));
}

static int		resolution(char *line, t_vars *vars, int *num)
{
	if (num[0])
		return (error_msg("Resolution set twice"));
	line++;
	while (*line == ' ')
		line++;
	if (ft_atoi(line) < vars->d_width)
		vars->d_width = ft_atoi(line);
	if (vars->d_width < 1)
		return (error_msg("Wrong resolution"));
	while (ft_isdigit(*line))
		line++;
	while (*line == ' ')
		line++;
	if (ft_atoi(line) < vars->d_height)
		vars->d_height = ft_atoi(line);
	if (vars->d_height < 1)
		return (error_msg("Wrong resolution"));
	while (ft_isdigit(*line))
		line++;
	if (*line)
		return (error_msg("Too many arguments in resolution"));
	num[0] = 1;
	return (1);
}

static int		check_line(char *line, t_vars *vars, int *num, int fd)
{
	if (*line == 'R' && *(line + 1) == ' ')
		return (resolution(line, vars, num));
	else if ((*line == 'N' && *(line + 1) == 'O') ||
				(*line == 'S' && *(line + 1) == 'O') ||
				(*line == 'W' && *(line + 1) == 'E') ||
				(*line == 'E' && *(line + 1) == 'A') ||
				(*line == 'S' && *(line + 1) == ' '))
		return (load_textures(vars, line, num));
	else if ((*line == 'F' && *(line + 1) == ' ') ||
				(*line == 'C' && *(line + 1) == ' '))
		return (floor_color(line, vars, num));
	else if ((*line == ' ' || *line == '1'))
		return (parse_map(line, vars, num, fd));
	else
		return (error_msg("Wrong file information"));
}

int				read_file(char *file_name, t_vars *vars)
{
	int		fd;
	char	*line;
	int		*num;

	num = ft_calloc(8, sizeof(int));
	if ((fd = open(file_name, O_RDONLY)) < 0)
		return (error_msg("Open error"));
	while (get_next_line(fd, &line) > 0)
	{
		if (*line)
			if (!check_line(line, vars, num, fd))
				return (check_free(vars, line, num, fd));
		free(line);
	}
	free(line);
	free(num);
	if (close(fd))
		return (error_msg("Close error"));
	return (1);
}
