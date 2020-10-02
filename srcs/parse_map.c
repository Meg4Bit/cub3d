/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 17:34:33 by ametapod          #+#    #+#             */
/*   Updated: 2020/10/02 15:33:32 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int		free_strings(char *map, char *line, char **tmp, char *msg)
{
	int		i;

	i = 0;
	if (map)
		free(map);
	if (line)
		free(line);
	if (tmp)
	{
		while (tmp[i])
			free(tmp[i++]);
		free(tmp);
	}
	return (error_msg(msg));
}

static int		check_str(char *map)
{
	int		i;

	i = 0;
	while (map[i])
	{
		if (map[i] == ' ')
			map[i] = '1';
		i++;
	}
	if (*map != '1' || *(ft_strrchr(map, 0) - 1) != '1')
		return (0);
	while (*map)
	{
		if (*map != '1' && *map != '2' && *map != '0' && *map != 'N' &&
					*map != 'S' && *map != 'W' && *map != 'E')
			return (0);
		if (*map != '1')
			return (-1);
		map++;
	}
	return (1);
}

static int		save_arr(char *map, int len, t_vars *vars)
{
	int		i;
	int		j;
	char	*begin;
	char	*tmp;

	if (!(vars->map = ft_split(map, '\n')))
		return (free_strings(map, 0, 0, "Malloc Error"));
	free(map);
	i = -1;
	while (vars->map[++i])
		if (ft_strlen(vars->map[i]) < (size_t)len)
		{
			j = 0;
			begin = vars->map[i];
			if (!(tmp = (char *)ft_calloc(len + 1, sizeof(char))))
				return (free_strings(0, 0, vars->map, "Malloc Error"));
			while (*(vars->map[i]))
				tmp[j++] = *(vars->map[i]++);
			while (j < len)
				tmp[j++] = '1';
			free(begin);
			vars->map[i] = tmp;
		}
	return (1);
}

static int		check_map(char **map, int fd, size_t len)
{
	int		i;
	int		last;
	char	*line;
	char	*tmp;

	i = 1;
	last = 1;
	while (get_next_line(fd, &line) > 0 || i-- > 0)
	{
		len = ft_strlen(line) > len ? ft_strlen(line) : len;
		if (!(last = check_str(line)))
			return (free_strings(*map, line, 0, "Invalid map"));
		if (!(tmp = ft_strjoin(*map, line)))
			return (free_strings(*map, line, 0, "Malloc Error"));
		free(*map);
		free(line);
		*map = tmp;
		if (!(tmp = ft_strjoin(*map, "\n")))
			return (free_strings(*map, 0, 0, "Malloc Error"));
		free(*map);
		*map = tmp;
	}
	free(line);
	return (last == -1 ? free_strings(*map, 0, 0, "Invalid map") : (int)len);
}

int				parse_map(char *line, t_vars *vars, int *num, int fd)
{
	int		i;
	int		len;
	char	*map;
	char	*tmp;

	i = 0;
	while (i < 8)
		if (!num[i++])
			return (error_msg("Wrong file information"));
	if (!(map = ft_strdup(line)))
		return (error_msg("Malloc Error"));
	if (check_str(map) != 1)
		return (free_strings(map, 0, 0, "Invalid map"));
	if (!(tmp = ft_strjoin(map, "\n")))
		return (free_strings(map, 0, 0, "Malloc Error"));
	free(map);
	map = tmp;
	if (!(len = check_map(&map, fd, ft_strlen(line))))
		return (0);
	return (save_arr(map, len, vars));
}
