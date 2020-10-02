/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ametapod <pe4enko111@rambler.ru>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 11:52:32 by ametapod          #+#    #+#             */
/*   Updated: 2020/10/02 21:45:49 by ametapod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define BUFFER_SIZE 128
# include <mlx.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "../libft/libft.h"

typedef struct		s_img {
	void			*img;
	char			*addr;
	int				bps;
	int				line_len;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef struct		s_pos {
	double			x;
	double			y;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			rot_speed;
	double			ms;
	double			move_hor;
	double			*wall_buf;
	double			*spr_dist;
}					t_pos;

typedef struct		s_ray {
	double			camerax;
	double			dirx;
	double			diry;
	double			side_distx;
	double			side_disty;
	double			delt_distx;
	double			delt_disty;
	double			perp2wall;
	double			wallx;
	int				stepx;
	int				stepy;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct		s_spray {
	int				move_spr;
	double			transx;
	double			transy;
	int				height;
	int				width;
	int				screenx;
	int				draw_startx;
	int				draw_endx;
	int				draw_starty;
	int				draw_endy;
}					t_spray;

typedef struct		s_sprite {
	double			x;
	double			y;
}					t_sprite;

typedef struct		s_vars {
	void			*mlx;
	void			*win;
	t_pos			*pos;
	t_img			*img;
	t_img			tex[5];
	t_sprite		*spr;
	char			**map;
	int				num_spr;
	int				d_width;
	int				d_height;
	int				ceil_color;
	int				floor_color;
}					t_vars;

typedef struct		s_bitmap_file_header {
	int				file_size;
	short			reserved1;
	short			reserved2;
	unsigned int	offset_bits;
}					t_bfh;

typedef struct		s_bitmap_image_header {
	unsigned int	size_header;
	unsigned int	width;
	unsigned int	height;
	short int		planes;
	short int		bit_count;
	unsigned int	compression;
	unsigned int	image_size;
	unsigned int	ppm_x;
	unsigned int	ppm_y;
	unsigned int	clr_used;
	unsigned int	clr_important;
}					t_bih;

void				my_mlx_pixel_put(t_img *data, int x, int y, int color);
int					create_rgb(int r, int g, int b);
void				clear_img(t_img *img, int x, int draw_start, int draw_end);
int					free_app(t_vars *vars, int flag, char *msg);
void				print_sprite(t_vars *vars, t_pos *pos);
t_ray				ray_casting(t_vars *vars, int x, t_img *img);
int					render_next_frame(t_vars *vars);
int					exit_hook(int keycode);
int					key_press_hook(int keycode, t_vars *vars);
int					key_release_hook(int keycode, t_vars *vars);
int					load_textures(t_vars *vars, char *line, int *num);
int					error_msg(char *msg);
int					check_args(int argc, char **argv);
int					read_file(char *file_name, t_vars *vars);
int					parse_map(char *line, t_vars *vars, int *num, int fd);
int					vars_setup(t_vars *vars);
int					create_bmp(t_vars *vars);

#endif
