/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buddha.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 22:01:49 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/16 19:20:32 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define BUDDHA_X -1.85
#define BUDDHA_Y -1.85

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
		while (it--)
			brighten_pixel(f->mlx->img[0], b[it].x, b[it].y, c);
}

void		*galaxy(t_info *f)
{
	double		tmp;
	double		y;
	t_buddha	b[f->it];
	t_complex	z;
	uint16_t	it;

	while (++f->x < f->x_max && (y = -1))
		while (++y < WIN_Y && (it = -1))
		{
			z.r = f->x / f->zoom + f->x_scale;
			z.i = y / f->zoom + f->y_scale;
			while (++it < f->it && z.r * z.r + z.i * z.i <= 4)
			{
				b[it].x = (z.r - f->x_scale) * f->zoom;
				b[it].y = (z.i - f->y_scale) * f->zoom;
				tmp = z.r;
				z.r = z.r * z.r - z.i * z.i + f->julia->cr;
				z.i = z.i * tmp;
				z.i += z.i + f->julia->ci;
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

	while (++f->x < f->x_max && (y = -1))
		while (++y < WIN_Y && (it = -1))
		{
			c.r = f->x / f->zoom + BUDDHA_X;
			c.i = y / f->zoom + BUDDHA_Y;
			z.r = 0;
			z.i = 0;
			while (++it < f->it && z.r * z.r + z.i * z.i <= 4)
			{
				b[it].x = (z.i - BUDDHA_Y) * f->zoom;
				b[it].y = (z.r - BUDDHA_X) * f->zoom;
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

	while (++f->x < f->x_max && (y = -1))
		while (++y < WIN_Y && (it = -1))
		{
			c.r = f->x / f->zoom + BUDDHA_X;
			c.i = y / f->zoom + BUDDHA_Y;
			z.r = 0;
			z.i = 0;
			while (++it < f->it && z.r * z.r + z.i * z.i <= 4)
			{
				b[it].x = (z.i - BUDDHA_Y) * f->zoom;
				b[it].y = (z.r - BUDDHA_X) * f->zoom;
				tmp = z.r;
				z.r = z.r * z.r - z.i * z.i + c.r;
				z.i = -2 * z.i * tmp + c.i;
			}
			draw_points(f, b, it);
		}
	pthread_exit(NULL);
}

