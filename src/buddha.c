/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddha.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 22:01:49 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/19 22:12:46 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	brighten_pixel(t_mlx_img *img, const int x, const int y, int color)
{
	char	*pos;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		BYEZ;
	pos = img->addr + (y * img->sl) + (x * img->bppx / 8);
	if (img->endian)
		color = ft_bswap(color);
	color += *(int *)pos;
	ft_memmove(pos, &color, sizeof(color));
}

static void	draw_points(t_info *f, const t_buddha b[], uint16_t it)
{
	int	c;

	c = (f->r * 5 % 255 << 16) + (f->g * 5 % 255 << 8) + f->b * 5 % 255;
	if (it < f->it && it >= f->noise)
	{
		if (f->thumb == false)
			while (it--)
				brighten_pixel(_DATA_MLX_IMG(f), b[it].x, b[it].y, c);
		else
			while (it--)
				if (b[it].x <= f->x_max && b[it].y <= f->y_max)
					brighten_pixel(_DATA_MLX_IMG(f), b[it].x, b[it].y, c);
	}
}

void		*galaxy(t_info *f)
{
	double		tmp;
	double		y;
	t_buddha	b[f->it];
	t_complex	z;
	uint16_t	it;

	while (++f->x < f->x_max && (y = f->y))
		while (++y < f->y_max && (it = -1))
		{
			z.r = f->x / f->zoom + f->x_scale + f->x_origin;
			z.i = y / f->zoom + f->y_scale + f->y_origin;
			while (++it < f->it && z.r * z.r + z.i * z.i <= 4)
			{
				b[it].x = (z.r - f->x_scale) * f->zoom;
				b[it].y = (z.i - f->y_scale) * f->zoom;
				tmp = z.r;
				z.r = z.r * z.r - z.i * z.i + f->julia->r;
				z.i = z.i * tmp;
				z.i += z.i + f->julia->i;
			}
			draw_points(f, b, it);
		}
	pthread_exit(NULL);
}

void		*buddhabrot(t_info *f)
{
	double		tmp;
	double		y;
	t_buddha	b[f->it];
	t_complex2	z;
	uint16_t	it;

	while (++f->x < f->x_max && (y = f->y))
		while (++y < f->y_max && (it = -1))
		{
			ft_memset(&z, '\0', sizeof(t_complex2));
			z.cr = f->x / f->zoom + f->x_scale + f->x_origin;
			z.ci = y / f->zoom + f->y_scale + f->y_origin;
			while (++it < f->it && z.zr * z.zr + z.zi * z.zi <= 4)
			{
				b[it].x = (!f->thumb ? z.zi - f->y_scale : z.zr - f->x_scale)\
					* f->zoom;
				b[it].y = (!f->thumb ? z.zr - f->x_scale : z.zi - f->y_scale)\
					* f->zoom;
				tmp = z.zr;
				z.zr = z.zr * z.zr - z.zi * z.zi + z.cr;
				z.zi = 2 * z.zi * tmp + z.ci;
			}
			draw_points(f, b, it);
		}
	pthread_exit(NULL);
}

void		*triforce(t_info *f)
{
	double		tmp;
	double		y;
	t_buddha	b[f->it];
	t_complex2	z;
	uint16_t	it;

	while (++f->x < f->x_max && (y = f->y))
		while (++y < f->y_max && (it = -1))
		{
			ft_memset(&z, '\0', sizeof(t_complex2));
			z.cr = f->x / f->zoom + f->x_scale + f->x_origin;
			z.ci = y / f->zoom + f->y_scale + f->y_origin;
			while (++it < f->it && z.zr * z.zr + z.zi * z.zi <= 4)
			{
				b[it].x = (!f->thumb ? z.zi - f->y_scale : z.zr - f->x_scale)\
					* f->zoom;
				b[it].y = (!f->thumb ? z.zr - f->x_scale : z.zi - f->y_scale)\
					* f->zoom;
				tmp = z.zr;
				z.zr = z.zr * z.zr - z.zi * z.zi + z.cr;
				z.zi = -2 * z.zi * tmp + z.ci;
			}
			draw_points(f, b, it);
		}
	pthread_exit(NULL);
}
