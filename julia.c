#include "fractol.h"

int calc_julia_point(struct complex c, int depth, double x, double y)
{
  struct complex z;
  double tmp;
  int i;

  z.r = x;
  z.i = y;
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


int	julia_zoom()
{

}
