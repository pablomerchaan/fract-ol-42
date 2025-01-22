#include "fractol.h"

t_fracdata *construct_fracdata(double zoom, double x, double y)
{
	void	*mlx;
	void	*mlx_win;
  t_fracdata *data;
  t_img *img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Fract-ol");

  img->img = mlx_new_image(mlx, 1920, 1080);
  img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
  data->mlx = mlx;
  data->mlx_win = mlx_win;
  data->img = img;
  data->zoom = zoom;
  data->x = x;
  data->y = y;
  return data;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
