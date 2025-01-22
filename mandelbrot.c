#include "fractol.h"

int calc_mandelbrot_point(struct complex c, int depth)
{
  struct complex z;
  double tmp;
  int i;

  z.r = 0;
  z.i = 0;
  i = 0;
  while (i < depth)
  {
    tmp = (z.r * z.r) + (z.i * z.i);
    //printf("TMP: %d\n", tmp);
    if (tmp > 4) {
      return 0;
    }
    else
    {
      tmp = z.r * z.r - z.i * z.i + c.r;
		  z.i = 2 * z.r * z.i + c.i;
		  z.r = tmp;
    }
    i++;
  }
  return 1;
}

void paint_fixed_mandelbrot(t_img *img, double z, double x, double y)
{
  int line;
  int column;
  int color;
  int in_set;
  struct complex point;

  line = 0;

  while (line < 1920)
  {
    column = 0;
    while (column < 1080) {
      point.r = ((double)line / z) + x;
      point.i = ((double)column / z) + y;
      in_set = calc_mandelbrot_point(point, 1000);
      if (in_set == 0)
      {
        color = create_trgb(0, 255, 0, 0);
      }
      else
      {
        color = create_trgb(0, 0, 255, 0);
      }
      my_mlx_pixel_put(img, line, column, color);
      column++;
    }
    line++;
  }
}

void mandelbrot_zoom(int key, t_fracdata *fracdata)
{
  double z;


	//mlx_clear_window(&fracdata->mlx, &fracdata->mlx_win);
  mlx_destroy_image(fracdata->mlx, fracdata->img->img);
	fracdata->img->img = mlx_new_image(fracdata->mlx, 1920, 1080);
  fracdata->img->addr = mlx_get_data_addr(fracdata->img->img, &fracdata->img->bits_per_pixel, &fracdata->img->line_length,
								&fracdata->img->endian);
	if (key == 4)
		z = fracdata->zoom / 1.1;
	else if (key == 5)
		z = fracdata->zoom * 1.1;
	paint_fixed_mandelbrot(fracdata->img, z, fracdata->x, fracdata->y);
  fracdata->zoom = z;
	mlx_put_image_to_window(fracdata->mlx, fracdata->mlx_win, fracdata->img->img, 0, 0);
}
