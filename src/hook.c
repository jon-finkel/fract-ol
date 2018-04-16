/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 00:38:13 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/16 19:08:33 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define _JULIA_RANGE 1.0

int			button(int button, int x, int y, t_info *f)
{
	(void)x;
	(void)y;
	if (button == X_SCROLL_DOWN)
		f->zoom *= 0.9;
	else if (button == X_SCROLL_UP)
		f->zoom *= 1.1;
	GIMME(!output(f) && !output_data(f));
}

static void	key2(int key, t_info *f)
{
	if (key == X_KEY_O && f->type == E_JULIA)
		f->orbital = (f->orbital == true ? false : true);
	if (key == X_KEY_P)
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
	else if (key == X_KEY_9 && f->noise >= 2)
		f->noise -= 2;
	else if (key == X_KEY_0 && f->noise <= UINT16_MAX - 2)
		f->noise += 2;
	else if (key == X_KEY_E && f->multi < UINT8_MAX)
		++f->multi;
	else if (key == X_KEY_Q && f->multi > 1)
		--f->multi;
}

int			key(int key, t_info *f)
{
	if (key == X_KEY_ESCAPE)
		terminate(f);
	else if (key == X_KEY_SPACE)
		reset_info(f);
	else if (key == X_KEY_T && (f->type == E_JULIA || f->type == E_GALAXY))
		f->lock = (f->lock ? false : true);
	else if (f->type < E_BUDDHA && key == X_KEY_W)
		f->y_scale += 100 / f->zoom;
	else if (f->type < E_BUDDHA && key == X_KEY_A)
		f->x_scale += 100 / f->zoom;
	else if (f->type < E_BUDDHA && key == X_KEY_S)
		f->y_scale -= 100 / f->zoom;
	else if (f->type < E_BUDDHA && key == X_KEY_D)
		f->x_scale -= 100 / f->zoom;
	else if (key == X_KEY_MINUS)
		f->it -= (f->it < 5 ? f->it : 5);
	else if (key == X_KEY_EQUAL)
		f->it += (f->it < 2000 ? 5 : 0);
	else
		key2(key, f);
	GIMME(!output(f) && !output_data(f));
}

int			motion(int x, int y, t_info *f)
{
	if ((f->type == E_JULIA || f->type == E_GALAXY)
		&& f->lock == false && f->orbital == false)
	{
		f->julia->ci = (y - WIN_Y / 2) / f->zoom;
		f->julia->cr = (x - WIN_X / 2) / f->zoom;
		GIMME(!output(f) && !output_data(f));
	}
	KTHXBYE;
}

int			psych(t_info *f)
{
	static bool	iclock = false;
	static bool	rclock = true;

	if (f->psych == true)
	{
		f->b += rand() % 10;
		f->g += rand() % 5;
		f->r += rand() % 15;
	}
	if (f->type == E_JULIA && f->lock == false && f->orbital == true)
	{
		if (f->julia->ci > _JULIA_RANGE || f->julia->ci < -_JULIA_RANGE)
			iclock = (iclock == true ? false : true);
		if (f->julia->cr > _JULIA_RANGE || f->julia->cr < -_JULIA_RANGE)
			rclock = (rclock == true ? false : true);
		f->julia->ci += (iclock == true ? 0.01 : -0.01);
		f->julia->cr += (rclock == true ? 0.01 : -0.01);
	}
	if (f->psych == true || f->orbital == true)
		GIMME(!output(f) && !output_data(f));
	KTHXBYE;
}
