#include <mlx.h>
#include "keys.h"

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct  s_pos {
    int         x;
    int         y;
}               t_pos;

typedef struct  s_vars {
    void        *mlx;
    void        *win;
    t_pos       *pos;
    t_data      *img;
}               t_vars;

void            my_mlx_pixel_put(t_data *data, int x_start, int y, int color, int x_len, int y_len)
{
    char    *dst;
    int     x;

    for (; y < y_len; y++)
    {
        x = x_start;
    for (; x < x_len; x++)
    {
        dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
    }
}

int             close(int keycode, t_vars *vars)
{
    if (keycode == 1)
        mlx_destroy_window(vars->mlx, vars->win);
    return (1);
}

int             move(int keycode, t_vars *vars)
{
    if (keycode == KEY_A)
        vars->pos->x--;
    if (keycode == KEY_W)
        vars->pos->y--;
    if (keycode == KEY_D)
        vars->pos->x++;
    if (keycode == KEY_S)
        vars->pos->y++;
    my_mlx_pixel_put(vars->img, vars->pos->x, vars->pos->y, 0x00FF0000, 50, 50);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, vars->pos->x, vars->pos->y);
    return (1);
}

int             main(void)
{
    t_vars  vars;
    t_data  img;
    t_pos   pos;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
    img.img = mlx_new_image(vars.mlx, 50, 50);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    vars.img = &img;
    vars.pos = &pos;
    pos.x = 5;
    pos.y = 5;
    my_mlx_pixel_put(&img, pos.x, pos.y, 0x00FF0000, 50, 50);
    mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
    mlx_mouse_hook(vars.win, close, &vars);
    mlx_key_hook(vars.win, move, &vars);
    mlx_loop(vars.mlx);
}