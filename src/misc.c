/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 00:59:45 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/23 11:08:20 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static const int	g_xthumb[3] =
{
	0,
	WIN_X / 4,
	WIN_X / 2
};

static const int	g_ythumb[5] =
{
	0,
	WIN_Y / 4,
	WIN_Y / 2,
	WIN_Y * 3 / 4,
	WIN_Y
};

static void	get_pos(t_info *info, const int8_t k)
{
	if (k % 2 == 0)
		info->x_scale = -1.998 * WIN_X / 1100.0;
	else
		info->x_scale = -5.998 * WIN_X / 1100.0;
	if (k >= 0 && k <= 1)
		info->y_scale = -2.001999 * WIN_Y / 1100.0;
	else if (k >= 2 && k <= 3)
		info->y_scale = -6.001999 * WIN_Y / 1100.0;
	else if (k >= 4 && k <= 5)
		info->y_scale = -10.001999 * WIN_Y / 1100.0;
	else if (k >= 6 && k <= 7)
		info->y_scale = -14.001999 * WIN_Y / 1100.0;
}

t_info		thumb_info(t_info *f, const int8_t k)
{
	t_info	info;

	info = *f;
	info.x = g_xthumb[k % 2] - 1;
	info.y = g_ythumb[k / 2] - 1;
	info.x_max = g_xthumb[k % 2 + 1];
	info.y_max = g_ythumb[k / 2 + 1];
	info.zoom = 68.5;
	if (f->thumbnails[k] == E_BUDDHA)
	{
		info.it = 2000;
		info.noise = 200;
	}
	else if (f->thumbnails[k] == E_GALAXY)
		info.it = 450;
	if (f->thumbnails[k] >= E_BUDDHA)
	{
		info.noise = 6;
		info.zoom = 66.2;
	}
	get_pos(&info, k);
	GIMME(info);
}

void		zoom(t_info *f, int x, int y, int key)
{
	double	xn;
	double	yn;
	double	xp;
	double	yp;

	xp = x / f->zoom + f->x_scale + f->x_origin;
	yp = y / f->zoom + f->y_scale + f->y_origin;
	f->zoom *= (key == X_SCROLL_DOWN ? 0.9 : 1.1);
	f->x_scale /= (key == X_SCROLL_DOWN ? 0.9 : 1.1);
	f->y_scale /= (key == X_SCROLL_DOWN ? 0.9 : 1.1);
	xn = x / f->zoom + f->x_scale + f->x_origin;
	yn = y / f->zoom + f->y_scale + f->y_origin;
	if ((key == X_SCROLL_UP && xn >= f->x_origin)
		|| (key == X_SCROLL_DOWN && xn < f->x_origin))
		f->x_origin += fdim(fmax(xn, xp), fmin(xn, xp));
	else
		f->x_origin -= fdim(fmax(xn, xp), fmin(xn, xp));
	if ((key == X_SCROLL_UP && yn >= f->y_origin)
		|| (key == X_SCROLL_DOWN && yn < f->y_origin))
		f->y_origin += fdim(fmax(yn, yp), fmin(yn, yp));
	else
		f->y_origin -= fdim(fmax(yn, yp), fmin(yn, yp));
}

t_type		*map_thumbnails(t_type *thumbnails, t_type current)
{
	int8_t	k;
	t_type	type;

	type = 0;
	k = -1;
	while (++k < 8)
	{
		if (type == current)
			++type;
		thumbnails[k] = type++;
	}
	GIMME(thumbnails);
}

void		reset_info(t_info *f)
{
	if (f->type == E_GALAXY)
		f->it = 450;
	else
		f->it = (f->type == E_BUDDHA ? 2000 : 100);
	f->x_origin = 0.0;
	f->y_origin = 0.0;
	f->x_scale = -1.998 * WIN_X / 1100.0;
	f->y_scale = -2.001999 * WIN_Y / 1100.0;
	f->multi = 2;
	f->r = (f->type == E_BUDDHA ? 9 : 11);
	f->g = 2;
	f->b = (f->type == E_BUDDHA ? 34 : 1);
	f->zoom = (f->type >= E_BUDDHA ? 300.0 : 270.0);
	f->julia->i = -0.27015;
	f->julia->r = -0.715;
	f->noise = (f->type == E_BUDDHA ? 200 : 6);
	f->lock = false;
	f->orbital = false;
	f->psych = false;
	f->thumb = false;
	f->rtu = false;
}
