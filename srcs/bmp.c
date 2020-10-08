/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:56:16 by ametapod          #+#    #+#             */
/*   Updated: 2020/10/05 13:14:49 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int		set_colors(t_vars *vars, int fd)
{
	char			*arr;
	int				i;
	int				j;
	int				size;
	unsigned int	color;

	size = vars->d_height * vars->d_width;
	if (!(arr = ft_calloc(size * 4, sizeof(char))))
		return (0);
	i = 0;
	j = 0;
	while (i < size)
	{
		color = *(unsigned int *)(vars->img->addr + i * (vars->img->bps / 8));
		arr[j++] = color & 255;
		arr[j++] = (color >> 8) & 255;
		arr[j++] = (color >> 16) & 255;
		arr[j++] = 0;
		i++;
	}
	j = write(fd, arr, size * 4);
	free(arr);
	return (1);
}

static void		set_bmp(t_vars *vars, t_bfh *bfh, t_bih *bih)
{
	int		image_size;
	int		ppm;

	image_size = 4 * vars->d_height * vars->d_width;
	ppm = 90 * 39.375;
	bfh->file_size = image_size + 54;
	bfh->reserved1 = 0;
	bfh->reserved2 = 0;
	bfh->offset_bits = 0;
	bih->size_header = sizeof(*bih);
	bih->width = vars->d_width;
	bih->height = -vars->d_height;
	bih->planes = 1;
	bih->bit_count = 32;
	bih->compression = 0;
	bih->image_size = image_size;
	bih->ppm_x = ppm;
	bih->ppm_y = ppm;
	bih->clr_used = 0;
	bih->clr_important = 0;
}

int				create_bmp(t_vars *vars)
{
	int		fd;
	int		wr;
	t_bfh	bfh;
	t_bih	bih;

	wr = 0;
	if ((fd = open("cub3D.bmp", O_WRONLY | O_CREAT |
							O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
		return (free_app(vars, 1, "Bmp create error"));
	set_bmp(vars, &bfh, &bih);
	wr = write(fd, "BM", 2);
	wr = write(fd, &bfh, sizeof(bfh));
	wr = write(fd, &bih, sizeof(bih));
	(void)wr;
	render_next_frame(vars);
	if (!set_colors(vars, fd))
		return (free_app(vars, 1, "Bmp create error"));
	if (close(fd))
		return (free_app(vars, 1, "Close error"));
	return (free_app(vars, 1, 0));
}
