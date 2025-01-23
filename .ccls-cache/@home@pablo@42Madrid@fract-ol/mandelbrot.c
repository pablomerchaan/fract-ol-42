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
      return i;
    }
    else
    {
      tmp = z.r * z.r - z.i * z.i + c.r;
		  z.i = 2 * z.r * z.i + c.i;
		  z.r = tmp;
    }
    i++;
  }
  return i;
}

int	get_color(double line, double column, double x, double y, double z)
{
  struct complex point;
  int in_set;
	int color;

	point.r = ((double)line / z) + x;
	point.i = ((double)column / z) + y;
	in_set = calc_mandelbrot_point(point, 1000);
	if (in_set == 1000)
    color = create_trgb(0, 0, 255, 0);
  else if (in_set < 20)
    color = create_trgb(0, 255, 0, 0);
  else if (in_set >= 30)
    color = create_trgb(0, 215, 40, 0);
  else if (in_set >= 40)
    color = create_trgb(0, 235, 20, 0);
  else if (in_set >= 50)
    color = create_trgb(0, 195, 60, 0);
  else if (in_set >= 60)
    color = create_trgb(0, 175, 80, 0);
  else if (in_set >= 80)
    color = create_trgb(0, 145, 110, 0);
  else if (in_set >= 100)
    color = create_trgb(0, 115, 140, 0);
  else if (in_set >= 120)
    color = create_trgb(0, 85, 170, 0);
  else if (in_set >= 150)
    color = create_trgb(0, 50, 205, 0);
	return (color);
}

void paint_fixed_mandelbrot(t_img *img, double z, double x, double y)
{
  int line;
  int column;
  int color;

  line = 0;
  while (line < 1920)
  {
    column = 0;
    while (column < 1080) {
			color = get_color(line, column, x, y, z);
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
