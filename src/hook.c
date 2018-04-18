/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 00:38:13 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/18 21:54:46 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define _JULIA_RANGE 1.0

static const t_thumbnails	g_thumbnails[8] =
{
	{0, WIN_X / 4, 0, WIN_Y / 4, 0},
	{WIN_X / 4, WIN_X / 2, 0, WIN_Y / 4, 1},
	{0, WIN_X / 4, WIN_Y / 4, WIN_Y / 2, 2},
	{WIN_X / 4, WIN_X / 2, WIN_Y / 4, WIN_Y / 2, 3},
	{0, WIN_X / 4, WIN_Y / 2, WIN_Y * 3 / 4, 4},
	{WIN_X / 4, WIN_X / 2, WIN_Y / 2, WIN_Y * 3 / 4, 5},
	{0, WIN_X / 4, WIN_Y * 3 / 4, WIN_Y, 6},
	{WIN_X / 4, WIN_X / 2, WIN_Y * 3 / 4, WIN_Y, 7}
};

int			button(int button, int x, int y, t_info *f)
{
	int		k;
	t_type	tmp;

	if (button == X_SCROLL_DOWN)
		f->zoom *= 0.9;
	else if (button == X_SCROLL_UP)
		f->zoom *= 1.1;
	else if (button == 1 && (x -= WIN_X) > 0)
	{
		k = -1;
		while (++k < 8)
			if (x >= g_thumbnails[k].x_begin && x < g_thumbnails[k].x_end
				&& y >= g_thumbnails[k].y_begin && y < g_thumbnails[k].y_end)
			{
				tmp = f->type;
				f->type = f->thumbnails[g_thumbnails[k].index];
				f->thumbnails[k] = tmp;
			}
		if (!f->rtu)
			reset_info(f);
		GIMME(!output(f, true) && !output_data(f));
	}
	GIMME(!output(f, f->rtu) && !output_data(f));
}

static void	key2(int key, t_info *f)
{
	if (key == X_KEY_O)
		f->orbital = (f->orbital == true ? false : true);
	else if (key == X_KEY_P)
		f->psych = (f->psych == true ? false : true);
	else if (key == X_KEY_1 || key == X_KEY_2)
		f->r += (key == X_KEY_2 ? 1 : -1);
	else if (key == X_KEY_3 || key == X_KEY_4)
		f->g += (key == X_KEY_4 ? 1 : -1);
	else if (key == X_KEY_5 || key == X_KEY_6)
		f->b += (key == X_KEY_6 ? 1 : -1);
	else if (key == X_KEY_7 || key == X_KEY_8)
	{
		f->r += (key == X_KEY_8 ? 1 : -1);
		f->g += (key == X_KEY_8 ? 1 : -1);
		f->b += (key == X_KEY_8 ? 1 : -1);
	}
	else if (key == X_KEY_9 && f->type >= E_GALAXY && f->noise < UINT16_MAX - 2)
		f->noise += 2;
	else if (key == X_KEY_0 && f->type >= E_GALAXY && f->noise > 2)
		f->noise -= 2;
	else if (key == X_KEY_E && f->multi < UINT8_MAX)
		++f->multi;
	else if (key == X_KEY_Q && f->multi > 1)
		--f->multi;
	else if (key == X_KEY_R)
		f->rtu = (f->rtu ? false : true);
}

int			key(int key, t_info *f)
{
	if (key == X_KEY_ESCAPE)
	{
		ftx_mlxdtor(f->mlx);
		exit(EXIT_SUCCESS);
	}
	else if (key == X_KEY_SPACE)
		reset_info(f);
	else if (key == X_KEY_T && (f->type == E_JULIA || f->type == E_GALAXY))
		f->lock = (f->lock ? false : true);
	else if (key == (f->type < E_BUDDHA ? X_KEY_W : X_KEY_A))
		f->y_scale += 100 / f->zoom;
	else if (key == (f->type < E_BUDDHA ? X_KEY_A : X_KEY_W))
		f->x_scale += 100 / f->zoom;
	else if (key == (f->type < E_BUDDHA ? X_KEY_S : X_KEY_D))
		f->y_scale -= 100 / f->zoom;
	else if (key == (f->type < E_BUDDHA ? X_KEY_D : X_KEY_S))
		f->x_scale -= 100 / f->zoom;
	else if (key == X_KEY_MINUS)
		f->it -= (f->it < 5 ? f->it : 5);
	else if (key == X_KEY_EQUAL)
		f->it += (f->it < 2000 ? 5 : 0);
	else
		key2(key, f);
	GIMME(!output(f, (key == X_KEY_SPACE ? true : f->rtu)) && !output_data(f));
}

int			motion(int x, int y, t_info *f)
{
	if ((f->type == E_JULIA || f->type == E_GALAXY)
		&& x >= 0 && x <= WIN_X && y >= 0 && y <= WIN_Y
		&& f->lock == false && f->orbital == false)
	{
		f->julia->i = (y - WIN_Y / 2) / f->zoom;
		f->julia->r = (x - WIN_X / 2) / f->zoom;
		GIMME(!output(f, f->rtu) && !output_data(f));
	}
	KTHXBYE;
}

int			loop(t_info *f)
{
	static bool	iclock = false;
	static bool	rclock = true;

	if (f->psych == true)
	{
		f->b += rand() % 7;
		f->g += rand() % 3;
		f->r += rand() % 11;
	}
	if (f->lock == false && f->orbital == true)
	{
		if (f->julia->i > _JULIA_RANGE || f->julia->i < -_JULIA_RANGE)
			iclock = (iclock == true ? false : true);
		if (f->julia->r > _JULIA_RANGE || f->julia->r < -_JULIA_RANGE)
			rclock = (rclock == true ? false : true);
		f->julia->i += (iclock == true ? 0.015 : -0.015);
		f->julia->r += (rclock == true ? 0.015 : -0.015);
	}
	if (f->psych == true || f->orbital == true)
		GIMME(!output(f, f->rtu) && !output_data(f));
	KTHXBYE;
}
