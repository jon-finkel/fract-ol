/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 00:38:13 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/15 17:22:35 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	reset_info(t_info *f)
{
	f->it = 100;
	f->x_scale = -2.85;
	f->y_scale = -1.55;
	f->r = 9;
	f->g = 2;
	f->b = 34;
	f->zoom = 250.0;
	f->julia->ci = -0.27015;
	f->julia->cr = -0.715;
	f->julia->lock = false;
}

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

static void	change_color(int key, t_info *f)
{
	if (key == X_KEY_1 || key == X_KEY_2)
		f->r += (key == X_KEY_2 ? 1 : -1);
	if (key == X_KEY_3 || key == X_KEY_4)
		f->g += (key == X_KEY_4 ? 1 : -1);
	if (key == X_KEY_5 || key == X_KEY_6)
		f->b += (key == X_KEY_6 ? 1 : -1);
	if (key == X_KEY_7 || key == X_KEY_8)
	{
		f->r += (key == X_KEY_8 ? 1 : -1);
		f->g += (key == X_KEY_8 ? 1 : -1);
		f->b += (key == X_KEY_8 ? 1 : -1);
	}
}

int			key(int key, t_info *f)
{
	if (key == X_KEY_ESCAPE)
		terminate(f);
	else if (key == X_KEY_SPACE)
		reset_info(f);
	else if (key == X_KEY_T && f->type == E_JULIA)
		f->julia->lock = (f->julia->lock ? false : true);
	else if ((f->type == E_BUDDHA && key == X_KEY_A)
		|| (f->type != E_BUDDHA && key == X_KEY_W))
		f->y_scale += 100 / f->zoom;
	else if ((f->type == E_BUDDHA && key == X_KEY_W)
		|| (f->type != E_BUDDHA && key == X_KEY_A))
		f->x_scale += 100 / f->zoom;
	else if ((f->type == E_BUDDHA && key == X_KEY_D)
		|| (f->type != E_BUDDHA && key == X_KEY_S))
		f->y_scale -= 100 / f->zoom;
	else if ((f->type == E_BUDDHA && key == X_KEY_S)
		|| (f->type != E_BUDDHA && key == X_KEY_D))
		f->x_scale -= 100 / f->zoom;
	else if (key == X_KEY_MINUS)
		f->it -= (f->it < 5 ? f->it : 5);
	else if (key == X_KEY_EQUAL)
		f->it += (f->it < 2000 ? 5 : 0);
	else
		change_color(key, f);
	GIMME(!output(f) && !output_data(f));
}

int			motion(int x, int y, t_info *f)
{
	if (f->type == E_JULIA && !f->julia->lock)
	{
		f->julia->ci = (y - WIN_Y / 2) / f->zoom;
		f->julia->cr = (x - WIN_X / 2) / f->zoom;
		GIMME(!output(f) && !output_data(f));
	}
	KTHXBYE;
}
