/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 14:13:32 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/15 16:06:15 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define BUDDHA_IT 2000
#define BUDDHA_THRESHOLD 500
#define BUDDHA_X -1.85
#define BUDDHA_Y -1.85
#define BUDDHA_ZOOM 300.0

static void	brighten_pixel(t_mlx_img *img, const int x, const int y, int color)
{
	char	*pos;

	if (x >= img->width || y >= img->height)
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

	c = (f->r * 10 << 16) + (f->g * 10 << 8) + f->b * 10;
	if (it < BUDDHA_IT && it >= BUDDHA_THRESHOLD)
		while (it--)
			brighten_pixel(f->mlx->img[0], b[it].x, b[it].y, c);
}

void		*buddhabrot(t_info *f)
{
	double		tmp;
	double		y;
	t_buddha	b[BUDDHA_IT];
	t_complex	z;
	uint16_t	it;

	while (++f->x < f->x_max && (y = -1))
		while (++y < WIN_Y && (it = -1))
		{
			z.cr = f->x / BUDDHA_ZOOM + BUDDHA_X;
			z.ci = y / BUDDHA_ZOOM + BUDDHA_Y;
			z.r = 0;
			z.i = 0;
			while (++it < BUDDHA_IT && z.r * z.r + z.i * z.i <= 4)
			{
				b[it].x = (z.i - BUDDHA_Y) * BUDDHA_ZOOM;
				b[it].y = (z.r - BUDDHA_X) * BUDDHA_ZOOM;
				tmp = z.r;
				z.r = z.r * z.r - z.i * z.i + z.cr;
				z.i = z.i * tmp;
				z.i += z.i + z.ci;
			}
			draw_points(f, b, it);
		}
	pthread_exit(NULL);
}
