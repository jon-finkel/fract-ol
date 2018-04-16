/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 01:02:15 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/16 18:56:48 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*fish(t_info *f)
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
				z.r = fabs(z.r * z.r - z.i * z.i) + c.r;
				z.i = 2 * z.i * tmp + c.i;
			}
			ftx_buffpixel(f->mlx->img[0], f->x, y,  (it == f->it || it == 1 ?\
				_BLACK : (it * f->r << 16) + (it * f->g << 8) + it * f->b));
		}
	pthread_exit(NULL);
}

void	*tricorn(t_info *f)
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
				z.r = z.r * z.r - z.i * z.i + c.r;
				z.i = -2 * z.i * tmp + c.i;
			}
			ftx_buffpixel(f->mlx->img[0], f->x, y,  (it == f->it || it == 1 ?\
				_BLACK : (it * f->r << 16) + (it * f->g << 8) + it * f->b));
		}
	pthread_exit(NULL);
}

void	*burning(t_info *f)
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
				z.r = z.r * z.r - z.i * z.i + c.r;
				z.i = fabs(z.i * tmp);
				z.i += z.i + c.i;
			}
			ftx_buffpixel(f->mlx->img[0], f->x, y,  (it == f->it || it == 1 ?\
				_BLACK : (it * f->r << 16) + (it * f->g << 8) + it * f->b));
		}
	pthread_exit(NULL);
}
