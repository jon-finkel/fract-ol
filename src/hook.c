/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 00:38:13 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/09 09:48:19 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_info	map_info(const t_info info)
{
	GIMME(((t_info){.x0 = info.x0, .x1 = info.x1, .y0 = info.y0, .y1 = info.y1,\
		.zoom = info.zoom, .x_max = ROUND((info.x1 - info.x0) * info.zoom),\
		.y_max = ROUND((info.y1 - info.y0) * info.zoom)}));
}

void			key_hook(int key, t_frac *frac)
{
	if (key == X_KEY_ESCAPE)
		terminate(frac);
	if (key == X_KEY_MINUS && frac->it)
		frac->it -= 10;
	else if (key == X_KEY_EQUAL && frac->it < _IT_MAX)
		frac->it += 10;
//	ftx_clearimg(frac->mlx->win[frac->mlx->cur_win]);
//	ftx_showimg(frac->mlx, 0, 0);
	output(frac->mlx, map_info(*frac->info), frac->it);
}

void			mouse_hook(int key, int x, int y, t_frac *frac)
{
	(void)x;
	(void)y;
	if (key == X_SCROLL_UP)
		frac->info->zoom += 10.0;
	else if (key == X_SCROLL_DOWN)
		frac->info->zoom -= 10.0;
//	ftx_clearimg(frac->mlx->win[frac->mlx->cur_win]);
//	ftx_showimg(frac->mlx, 0, 0);
	output(frac->mlx, map_info(*frac->info), frac->it);
}
