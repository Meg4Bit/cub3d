#include <mlx.h>
#include "keys.h"
#include <math.h>
#include <stdio.h>

int worldMap[24][24]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct  s_pos {
    double      posX;
    double      posY;
    double      dirX;
    double      dirY;
    double      planeX;
    double      planeY;
    double      cameraX;
    double      rayDirX;
    double      rayDirY;
    double      sideDistX;
    double      sideDistY;
    double      deltaDistX;
    double      deltaDistY;
    double      perpWallDist;
}               t_pos;

typedef struct  s_vars {
    void        *mlx;
    void        *win;
    t_pos       *pos;
    t_data      *img;
}               t_vars;

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             close(int keycode, t_vars *vars)
{
    if (keycode == 1)
        mlx_destroy_window(vars->mlx, vars->win);
    return (1);
}

void            verLine(t_data *img, int x, int drawStart, int drawEnd, int color)
{
    int y;

    y = drawStart;
    for (; y <= drawEnd; y++)
      my_mlx_pixel_put(img, x, y, color);
}

int            render_next_frame(t_vars *vars)
{
    int     width = 800;
    int     h = 800;

    for(int x = 0; x < width; x++)
      verLine(vars->img, x, 0, h - 1, 0x00000000);
    for(int x = 0; x < width; x++)
    {
      //calculate ray position and direction
      vars->pos->cameraX = 2 * x / (double)width - 1; //x-coordinate in camera space
      vars->pos->rayDirX = vars->pos->dirX + vars->pos->planeX * vars->pos->cameraX;
      vars->pos->rayDirY = vars->pos->dirY + vars->pos->planeY * vars->pos->cameraX;
      //which box of the map we're in
      int mapX = vars->pos->posX;
      int mapY = vars->pos->posY;

      vars->pos->deltaDistX = fabs(1 / vars->pos->rayDirX);
      vars->pos->deltaDistY = fabs(1 / vars->pos->rayDirY);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist
      if(vars->pos->rayDirX < 0)
      {
        stepX = -1;
        vars->pos->sideDistX = (vars->pos->posX - mapX) * vars->pos->deltaDistX;
      }
      else
      {
        stepX = 1;
        vars->pos->sideDistX = (mapX + 1.0 - vars->pos->posX) * vars->pos->deltaDistX;
      }
      if(vars->pos->rayDirY < 0)
      {
        stepY = -1;
        vars->pos->sideDistY = (vars->pos->posY - mapY) * vars->pos->deltaDistY;
      }
      else
      {
        stepY = 1;
        vars->pos->sideDistY = (mapY + 1.0 - vars->pos->posY) * vars->pos->deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if(vars->pos->sideDistX < vars->pos->sideDistY)
        {
          vars->pos->sideDistX += vars->pos->deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          vars->pos->sideDistY += vars->pos->deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(worldMap[mapX][mapY] > 0) hit = 1;
      }
      //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      if(side == 0) perpWallDist = (mapX - vars->pos->posX + (1 - stepX) / 2) / vars->pos->rayDirX;
      else          perpWallDist = (mapY - vars->pos->posY + (1 - stepY) / 2) / vars->pos->rayDirY;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h)drawEnd = h - 1;

      //choose wall color
      int color;
      switch(worldMap[mapX][mapY])
      {
        case 1:  color = 0x00FF0000;    break; //red
        case 2:  color = 0x0000FF00;  break; //green
        case 3:  color = 0x000000FF;   break; //blue
        case 4:  color = 0x00FFFFFF;  break; //white
        default: color = 0x00000000; break; //yellow
      }

      //give x and y sides different brightness
      //if(side == 1) {color = color / 2;}

      //draw the pixels of the stripe as a vertical line
      verLine(vars->img, x, drawStart, drawEnd, color);
    }
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
    return (1);
}

/*int             key_press_hook(int keycode, t_vars *vars)
{
    double moveSpeed = 0.01 * 5.0;

    keycode--;
    if(!worldMap[(int)(vars->pos->posX + vars->pos->dirX * moveSpeed)][(int)(vars->pos->posY)]) vars->pos->posX += vars->pos->dirX * moveSpeed;
    if(!worldMap[(int)(vars->pos->posX)][(int)(vars->pos->posY + vars->pos->dirY * moveSpeed)]) vars->pos->posY += vars->pos->dirY * moveSpeed;
    return 1;
}*/

int             key_press_hook(int keycode, t_vars *vars)
{
    double rotSpeed = 0.01 * 3.0;
    double moveSpeed = 0.01 * 5.0;

    if (keycode == 0xff53)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = vars->pos->dirX;
      vars->pos->dirX = vars->pos->dirX * cos(-rotSpeed) - vars->pos->dirY * sin(-rotSpeed);
      vars->pos->dirY = oldDirX * sin(-rotSpeed) + vars->pos->dirY * cos(-rotSpeed);
      double oldPlaneX = vars->pos->planeX;
      vars->pos->planeX = vars->pos->planeX * cos(-rotSpeed) - vars->pos->planeY * sin(-rotSpeed);
      vars->pos->planeY = oldPlaneX * sin(-rotSpeed) +vars->pos-> planeY * cos(-rotSpeed);
    }
    if (keycode == 0xff51)
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = vars->pos->dirX;
      vars->pos->dirX = vars->pos->dirX * cos(rotSpeed) - vars->pos->dirY * sin(rotSpeed);
      vars->pos->dirY = oldDirX * sin(rotSpeed) + vars->pos->dirY * cos(rotSpeed);
      double oldPlaneX = vars->pos->planeX;
      vars->pos->planeX = vars->pos->planeX * cos(rotSpeed) - vars->pos->planeY * sin(rotSpeed);
      vars->pos->planeY = oldPlaneX * sin(rotSpeed) + vars->pos->planeY * cos(rotSpeed);
    }
    if (keycode == 0x0077)
    {
      if(!worldMap[(int)(vars->pos->posX + vars->pos->dirX * moveSpeed)][(int)(vars->pos->posY)]) vars->pos->posX += vars->pos->dirX * moveSpeed;
      if(!worldMap[(int)(vars->pos->posX)][(int)(vars->pos->posY + vars->pos->dirY * moveSpeed)]) vars->pos->posY += vars->pos->dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if (keycode == 0x0073)
    {
      if(!worldMap[(int)(vars->pos->posX - vars->pos->dirX * moveSpeed)][(int)(vars->pos->posY)]) vars->pos->posX -= vars->pos->dirX * moveSpeed;
      if(!worldMap[(int)(vars->pos->posX)][(int)(vars->pos->posY - vars->pos->dirY * moveSpeed)]) vars->pos->posY -= vars->pos->dirY * moveSpeed;
    }
    return (1);
}

int             main(void)
{
    t_vars  vars;
    t_data  img;
    t_pos   pos;
    int     width = 800;
    int     h = 800;

    pos.posX = 22;
    pos.posY = 12;
    pos.dirX = 0;
    pos.dirY = -1;
    pos.planeX = -0.66;
    pos.planeY = 0;

    /*double time = 0; //time of current frame
    double oldTime = 0; //time of previous frame*/

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, width, h, "Hello world!");
    img.img = mlx_new_image(vars.mlx, width, h);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
                                 &img.endian);
    vars.img = &img;
    vars.pos = &pos;
    //mlx_mouse_hook(vars.win, close, &vars);
    //mlx_key_hook(vars.win, move, &vars);
    mlx_hook(vars.win, 2, (1L<<0), key_press_hook, &vars);
    mlx_loop_hook(vars.mlx, render_next_frame, &vars);
    mlx_loop(vars.mlx);
}