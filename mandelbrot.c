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

int	get_color(double line, double column, t_fracdata data, double z)
{
  struct complex point;
  int in_set;
	int color;

	point.r = ((double)line / z) + data.x;
	point.i = ((double)column / z) + data.y;
	if(ft_strcmp(data.name, "mandelbrot"))
		in_set = calc_mandelbrot_point(point, 1000);
	if(ft_strcmp(data.name, "julia"))
		in_set = calc_julia_point(point, 1000, 1.01, 0.3);
	if (in_set == 1000)
    color = create_trgb(0, 0, 255, 0);
  else if (in_set < 20)
    color = create_trgb(0, 255, 0, 0);
  else if (in_set >= 30)
    color = create_trgb(0, 185, 40, 30);
  else if (in_set <= 40)
    color = create_trgb(0, 205, 20, 30);
  else if (in_set <= 50)
    color = create_trgb(0, 165, 60, 30);
  else if (in_set <= 60)
    color = create_trgb(0, 155, 70, 30);
  else if (in_set <= 80)
    color = create_trgb(0, 100, 100, 55);
  else if (in_set <= 100)
    color = create_trgb(0, 95, 120, 40);
  else if (in_set <= 120)
    color = create_trgb(0, 85, 170, 0);
  else if (in_set > 120)
    color = create_trgb(0, 50, 205, 0);
	return (color);
}

void paint_fixed_fractal(t_fracdata data, double z)
{
  int line;
  int column;
  int color;

	printf("PAINT\n");
  line = 0;
  while (line < 1920)
  {
    column = 0;
    while (column < 1080) {
			color = get_color(line, column, data, z);
      my_mlx_pixel_put(data.img, line, column, color);
      column++;
    }
    line++;
  }
}

void zoom(int key, t_fracdata *fracdata)
{
  double z;
	printf("ZOOM\n");
	//mlx_clear_window(&fracdata->mlx, &fracdata->mlx_win);
  mlx_destroy_image(fracdata->mlx, fracdata->img->img);
	fracdata->img->img = mlx_new_image(fracdata->mlx, 1920, 1080);
  fracdata->img->addr = mlx_get_data_addr(fracdata->img->img, &fracdata->img->bits_per_pixel, &fracdata->img->line_length,
								&fracdata->img->endian);
	if (key == 4)
		z = fracdata->zoom / 1.1;
	else if (key == 5)
		z = fracdata->zoom * 1.1;
	paint_fixed_fractal(*fracdata, z);
  fracdata->zoom = z;
	mlx_put_image_to_window(fracdata->mlx, fracdata->mlx_win, fracdata->img->img, 0, 0);
}
