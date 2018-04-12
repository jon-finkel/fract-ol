/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 00:38:13 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/13 01:05:52 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	reset_info(t_info *f)
{
	f->it = 100;
	f->x_scale = -3.7;
	f->y_scale = -2.1;
	f->r = 11;
	f->g = 0;
	f->b = 0;
	f->zoom = 250.0;
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

static void	change_fractal(int key, t_info *f)
{
	if (key == X_KEY_0)
		f->type = E_MANDEL;
	else if (key == X_KEY_1)
		f->type = E_BURNING;
}

int			key(int key, t_info *f)
{
	if (key == X_KEY_ESCAPE)
		terminate(f);
	else if (key == X_KEY_SPACE)
		reset_info(f);
	else if (key == X_KEY_W)
		f->y_scale += 100 / f->zoom;
	else if (key == X_KEY_A)
		f->x_scale += 100 / f->zoom;
	else if (key == X_KEY_S)
		f->y_scale -= 100 / f->zoom;
	else if (key == X_KEY_D)
		f->x_scale -= 100 / f->zoom;
	else if (key == X_KEY_MINUS)
		f->it -= (f->it < 5 ? f->it : 5);
	else if (key == X_KEY_EQUAL)
		f->it += (f->it < 2000 ? 5 : 0);
	else
		change_fractal(key, f);
	GIMME(!output(f) && !output_data(f));
}

int			motion(int x, int y, t_info *f) //TODO julia
{
	(void)x;
	(void)y;
	(void)f;
	GIMME(!output(f) && !output_data(f));
}
