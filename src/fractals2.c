/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 14:13:32 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/15 22:02:52 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*firebrot(t_info *f)
{
	double		tmp;
	double		y;
	int			c;
	t_complex	z;
	uint16_t	it;

	while (++f->x < f->x_max && (y = -1))
		while (++y < WIN_Y && (it = -1))
		{
			z.cr = f->x / f->zoom + f->x_scale;
			z.ci = y / f->zoom + f->y_scale;
			z.r = 0;
			z.i = 0;
			while (++it < f->it && z.r * z.r + z.i * z.i <= 4)
			{
				tmp = z.r;
				z.r = sin(z.r * z.r - z.i * z.i) + z.cr;
				z.i = z.i * tmp;
				z.i += z.i + z.ci;
			}
			c = (it == f->it || it == 1 ? _BLACK\
				: (it * f->r << 16) + (it * f->g << 8) + it * f->b);
			ftx_buffpixel(f->mlx->img[0], f->x, y, c);
		}
	pthread_exit(NULL);
}
