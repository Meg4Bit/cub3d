/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 12:14:46 by ametapod          #+#    #+#             */
/*   Updated: 2020/09/29 12:15:47 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void			my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bps / 8));
	*(unsigned int*)dst = color;
}

int				create_rgb(int r, int g, int b)
{
	return(r << 16 | g << 8 | b);
}

void			clear_img(t_img *img, int x, int draw_start, int draw_end)
{
	int y;

	y = draw_start;
	while (y <= draw_end)
		my_mlx_pixel_put(img, x, y++, 0);
}