/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 00:59:45 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/16 19:22:40 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
