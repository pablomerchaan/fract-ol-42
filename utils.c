#include "fractol.h"

t_fracdata *construct_fracdata(t_fracdata *data, double zoom, double x, double y, char **argv)
{
	void	*mlx_win;
  t_img *img;
	char *name;
	int	c;

	c = 0;
	printf("BEFORE COSTRUCTFRACDATA\n");
	name = malloc(ft_strlen(argv[1]) * sizeof(char));
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "Fract-ol");
  img->img = mlx_new_image(data->mlx, 1920, 1080);
	printf("BEFORE NAME\n");
  img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length,
								&img->endian);
	while (argv[1][c])
	{
		name[c] = argv[1][c];
		c++;
	}
	name[c] = '\0';
	printf("AFTER NAME\n");
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

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
