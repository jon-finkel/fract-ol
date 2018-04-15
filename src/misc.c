/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 00:59:45 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/15 18:30:11 by nfinkel          ###   ########.fr       */
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
	f->psych = false;
	f->it = 100;
	f->x_scale = -1.998;
	f->y_scale = -2.001999;
	f->r = (f->type == E_BUDDHA ? 9 : 11);
	f->g = 2;
	f->b = (f->type == E_BUDDHA ? 34 : 1);
	f->zoom = 250.0;
	f->julia->ci = -0.27015;
	f->julia->cr = -0.715;
	f->julia->lock = false;
}
