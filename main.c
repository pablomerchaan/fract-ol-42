#include "fractol.h"

int	on_mouse_hook(int key, int x, int y, void *data)
{
  t_fracdata *fracdata;

  printf("In hook\n");
  fracdata = (t_fracdata *)data;
	if (key == 4)
	{
		fracdata->x = (x / fracdata->zoom + fracdata-> x) - (x / (fracdata->zoom / 1.1));
		fracdata->y = (y / fracdata->zoom + fracdata-> y) - (y / (fracdata->zoom / 1.1));
	}
	if (key == 5)
	{
		fracdata->x = (x / fracdata->zoom + fracdata-> x) - (x / (fracdata->zoom * 1.1));
		fracdata->y = (y / fracdata->zoom + fracdata-> y) - (y / (fracdata->zoom * 1.1));
	}
	if (key == 4 || key == 5)
		mandelbrot_zoom(key, fracdata);

  return(0);
}

int	on_key_hook(int key, t_fracdata *data)
{
	if (key == 65307)
	{
		mlx_destroy_image(data->mlx, data->img->img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		exit(0);
	}
	return (0);
}

int	main(void)
{
  static double z;
  static double x;
  static double y;
  t_fracdata *data;

  z = 500;
  x = 0;
  y = 0;
  data = construct_fracdata(z, x, y);
  paint_fixed_mandelbrot(data->img, z, x, y);
  mlx_put_image_to_window(data->mlx, data->mlx_win, data->img->img, 0, 0);
	mlx_mouse_hook(data->mlx_win, *on_mouse_hook, data);
	mlx_key_hook(data->mlx_win, on_key_hook, data);
	mlx_loop(data->mlx);
}
