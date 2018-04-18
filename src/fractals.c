/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 01:02:15 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/18 13:24:18 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*fish(t_info *f)
{
	double		y;
	t_complex	c;
	t_complex	tmp;
	t_complex	z;
	uint16_t	it;

	while (++f->x < f->x_max && (y = f->y))
		while (++y < f->y_max && (it = -1))
		{
			c.r = f->x / f->zoom + f->x_scale;
			c.i = y / f->zoom + f->y_scale;
			ft_memset(&z, '\0', sizeof(t_complex));
			while (++it < f->it && z.r * z.r + z.i * z.i <= 4)
			{
				tmp = z;
				z.r = fabs(ft_zpowr(z, f->multi)) + c.r;
				z.i = ft_zpowi(tmp, f->multi) + c.i;
			}
			ftx_buffpixel(_DATA_MLX_IMG(f), f->x, y, (it == f->it || it == 1 ?\
				_BLACK : (it * f->r << 16) + (it * f->g << 8) + it * f->b));
		}
	pthread_exit(NULL);
}

void	*tricorn(t_info *f)
{
	double		y;
	t_complex	c;
	t_complex	tmp;
	t_complex	z;
	uint16_t	it;

	while (++f->x < f->x_max && (y = f->y))
		while (++y < f->y_max && (it = -1))
		{
			c.r = f->x / f->zoom + f->x_scale;
			c.i = y / f->zoom + f->y_scale;
			ft_memset(&z, '\0', sizeof(t_complex));
			while (++it < f->it && z.r * z.r + z.i * z.i <= 4)
			{
				tmp = z;
				z.r = ft_zpowr(z, f->multi) + c.r;
				z.i = -ft_zpowi(tmp, f->multi) + c.i;
			}
			ftx_buffpixel(_DATA_MLX_IMG(f), f->x, y, (it == f->it || it == 1 ?\
				_BLACK : (it * f->r << 16) + (it * f->g << 8) + it * f->b));
		}
	pthread_exit(NULL);
}

void	*burning(t_info *f)
{
	double		y;
	t_complex	c;
	t_complex	tmp;
	t_complex	z;
	uint16_t	it;

	while (++f->x < f->x_max && (y = f->y))
		while (++y < f->y_max && (it = -1))
		{
			c.r = f->x / f->zoom + f->x_scale;
			c.i = y / f->zoom + f->y_scale;
			ft_memset(&z, '\0', sizeof(t_complex));
			while (++it < f->it && z.r * z.r + z.i * z.i <= 4)
			{
				tmp = z;
				z.r = ft_zpowr(z, f->multi) + c.r;
				z.i = fabs(ft_zpowi(tmp, f->multi)) + c.i;
			}
			ftx_buffpixel(_DATA_MLX_IMG(f), f->x, y, (it == f->it || it == 1 ?\
				_BLACK : (it * f->r << 16) + (it * f->g << 8) + it * f->b));
		}
	pthread_exit(NULL);
}
