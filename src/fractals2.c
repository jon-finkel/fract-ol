/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 14:13:32 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/16 18:56:33 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*firebrot(t_info *f)
{
	double		tmp;
	double		y;
	t_complex	c;
	t_complex	z;
	uint16_t	it;

	while (++f->x < f->x_max && (y = -1))
		while (++y < WIN_Y && (it = -1))
		{
			c.r = f->x / f->zoom + f->x_scale;
			c.i = y / f->zoom + f->y_scale;
			z.r = 0;
			z.i = 0;
			while (++it < f->it && z.r * z.r + z.i * z.i <= 4)
			{
				tmp = z.r;
				z.r = sin(z.r * z.r - z.i * z.i) + c.r;
				z.i = z.i * tmp;
				z.i += z.i + c.i;
			}
			ftx_buffpixel(f->mlx->img[0], f->x, y,  (it == f->it || it == 1 ?\
				_BLACK : (it * f->r << 16) + (it * f->g << 8) + it * f->b));
		}
	pthread_exit(NULL);
}

void	*mandelbrot(t_info *f)
{
	double		y;
	t_complex	c;
	t_complex	z;
	t_complex	tmp;
	uint16_t	it;

	while (++f->x < f->x_max && (y = -1))
		while (++y < WIN_Y && (it = -1))
		{
			c.r = f->x / f->zoom + f->x_scale;
			c.i = y / f->zoom + f->y_scale;
			z.r = 0;
			z.i = 0;
			while (++it < f->it && z.r * z.r + z.i * z.i <= 4)
			{
				tmp = z;
				z.r = ft_zpowr(z, f->multi) + c.r;
				z.i = ft_zpowi(tmp, f->multi) + c.i;
			}
			ftx_buffpixel(f->mlx->img[0], f->x, y,  (it == f->it || it == 1 ?\
				_BLACK : (it * f->r << 16) + (it * f->g << 8) + it * f->b));
		}
	pthread_exit(NULL);
}

void	*julia(t_info *f)
{
	double		y;
	t_complex	z;
	t_complex	tmp;
	uint16_t	it;

	while (++f->x < f->x_max && (y = -1))
		while (++y < WIN_Y && (it = -1))
		{
			z.r = f->x / f->zoom + f->x_scale;
			z.i = y / f->zoom + f->y_scale;
			while (++it < f->it && z.r * z.r + z.i * z.i <= 4)
			{
				tmp = z;
				z.r = ft_zpowr(z, f->multi) + f->julia->cr;
				z.i = ft_zpowi(tmp, f->multi) + f->julia->ci;
			}
			ftx_buffpixel(f->mlx->img[0], f->x, y,  (it == f->it || it == 1 ?\
				_BLACK : (it * f->r << 16) + (it * f->g << 8) + it * f->b));
		}
	pthread_exit(NULL);
}
