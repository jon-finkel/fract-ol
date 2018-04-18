/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddha.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 22:01:49 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/18 07:31:15 by nfinkel          ###   ########.fr       */
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

	c = (f->r * 5 << 16) + (f->g * 5 << 8) + f->b * 5;
	if (it < f->it && it >= f->noise)
	{
		if (f->thumb_noise == false)
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
			z.r = f->x / f->zoom + f->x_scale;
			z.i = y / f->zoom + f->y_scale;
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
	t_complex	c;
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
				b[it].x = (f->invert ? z.i - f->y_scale : z.r - f->x_scale)\
					* f->zoom;
				b[it].y = (f->invert ? z.r - f->x_scale : z.i - f->y_scale)\
					* f->zoom;
				tmp = z.r;
				z.r = z.r * z.r - z.i * z.i + c.r;
				z.i = z.i * tmp;
				z.i += z.i + c.i;
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
	t_complex	c;
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
				b[it].x = (f->invert ? z.i - f->y_scale : z.r - f->x_scale)\
					* f->zoom;
				b[it].y = (f->invert ? z.r - f->x_scale : z.i - f->y_scale)\
					* f->zoom;
				tmp = z.r;
				z.r = z.r * z.r - z.i * z.i + c.r;
				z.i = -2 * z.i * tmp + c.i;
			}
			draw_points(f, b, it);
		}
	pthread_exit(NULL);
}
