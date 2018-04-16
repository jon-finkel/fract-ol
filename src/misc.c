/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 00:59:45 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/16 23:37:45 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static const int	g_xthumb[5] =
{
	WIN_X,
	WIN_X + WIN_X / 8,
	WIN_X + WIN_X / 4,
	WIN_X + WIN_X * 3 / 8,
	WIN_X + WIN_X / 2
};

static const int	g_ythumb[5] =
{
	0,
	WIN_Y / 4,
	WIN_Y / 2,
	WIN_Y * 3 / 4,
	WIN_Y
};

t_info	thumb_info(t_info *f, const int8_t k)
{
	t_info	info;

	info = *f;
	info.x = g_xthumb[k % 4] - 1;
	info.y = g_ythumb[k / 4] - 1;
	info.x_max = g_xthumb[k % 4 + 1] + 1;
	info.y_max = g_ythumb[k / 4 + 1] + 1;
	info.zoom = 65.0;
	if (k == 0 || k == 1)
	{
		info.x_scale = -18.903265;
		info.y_scale = -2.145740;
	}
	else if (k == 1 || k == 2)
	{
		info.x_scale = -22.903265;
		info.y_scale = -2.145740;
	}
	GIMME(info);
}

void	terminate(t_info *f)
{
	ftx_mlxdtor(f->mlx);
	exit(EXIT_SUCCESS);
}

void	reset_info(t_info *f)
{
	f->orbital = false;
	f->psych = false;
	if (f->type == E_GALAXY)
		f->it = 450;
	else
		f->it = (f->type == E_BUDDHA ? 2000 : 100);
	f->x_scale = -1.998;
	f->y_scale = -2.001999;
	f->multi = 2;
	f->r = (f->type == E_BUDDHA ? 9 : 11);
	f->g = 2;
	f->b = (f->type == E_BUDDHA ? 34 : 1);
	f->zoom = (f->type >= E_BUDDHA ? 300.0 : 250.0);
	f->julia->ci = -0.27015;
	f->julia->cr = -0.715;
	f->lock = false;
	f->noise = (f->type == E_BUDDHA ? 200 : 6);
}
