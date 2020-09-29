/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:52:32 by ametapod          #+#    #+#             */
/*   Updated: 2020/09/29 12:16:09 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <mlx.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct	s_img {
	void		*img;
	char		*addr;
	int			bps;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct  s_pos {
	double		x;
	double		y;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		rot_speed;
	double		move_speed;
	double		move_hor;
	double		*wall_buf;
	double		sprDist[2];
}				t_pos;

typedef struct	s_ray {
	double		camerax;
	double		dirx;
	double		diry;
	double		side_distx;
	double		side_disty;
	double		delt_distx;
	double		delt_disty;
	double		perp2wall;
	double		wallx;
	int			stepx;
	int			stepy;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

typedef struct	s_spRay {
	int			move_spr;
	double		transx;
	double		transy;
	int			height;
	int			width;
	int			screenx;
	int			draw_startx;
	int			draw_endx;
	int			draw_starty;
	int			draw_endy;
}				t_spRay;

typedef struct	s_sprite {
	double		x;
	double		y;
}				t_sprite;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_pos		*pos;
	t_img		*img;
	t_img		tex[5];
	t_sprite	spr[2];
	int			num_spr;
	int			d_width;
	int			d_height;
	int			ceil_color;
	int			floor_color;
}				t_vars;

void			my_mlx_pixel_put(t_img *data, int x, int y, int color);
int				create_rgb(int r, int g, int b);
void			clear_img(t_img *img, int x, int draw_start, int draw_end);

#endif
