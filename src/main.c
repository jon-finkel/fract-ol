/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:41:34 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/13 01:02:36 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define WIN_TITLE "fractol"
#define BUFF_SIZE (128)

static const char				*g_usage =
{
	"usage: ./fractol [burning_ship | julia | mandelbrot]"
};

static const struct s_fractal	g_fractal[3] =
{
	{"Burning Ship", burning},
	{"Julia", burning},
	{"Mandelbrot", mandelbrot}
};

static t_type	get_args(int argc, const char *s)
{
	if (argc == 2)
	{
		if (ft_strequ(s, "burning_ship"))
			GIMME(E_BURNING);
		else if (ft_strequ(s, "julia"))
			GIMME(E_JULIA);
		else if (ft_strequ(s, "mandelbrot"))
			GIMME(E_MANDEL);
	}
	ft_printf("%s\n", g_usage);
	GIMME(E_NULL);
}

int				output(t_info *f)
{
	int			k;
	pthread_t	th[THREADS];
	t_info		info[THREADS];

	ftx_clearwin(f->mlx);
	k = -1;
	while (++k < THREADS)
	{
		info[k] = *f;
		info[k].x = ((WIN_X / THREADS) * k) - 1;
		info[k].x_max = (WIN_X / THREADS) * (k + 1) + 1;
		pthread_create(th + k, NULL, (void *(*)(void *))g_fractal[f->type].f,\
			info + k);
	}
	while (k--)
		pthread_join(th[k], NULL);
	ftx_showimg(f->mlx, 0, 0);
	KTHXBYE;
}

int				output_data(t_info *f)
{
	char	buff[BUFF_SIZE];

	mlx_string_put(f->mlx->mlx, f->mlx->win[0], 0, 0, _WHITE, " --- DATA ---");
	ft_snprintf(buff, BUFF_SIZE, " ZOOM: x%.f", f->zoom);
	mlx_string_put(f->mlx->mlx, f->mlx->win[0], 0, 15, _WHITE, buff);
	ft_snprintf(buff, BUFF_SIZE, " ITER: %hu", f->it);
	mlx_string_put(f->mlx->mlx, f->mlx->win[0], 0, 30, _WHITE, buff);
	KTHXBYE;
}

int				main(int argc, const char *argv[])
{
	t_info	f;
	t_mlx	mlx_stack;

	if ((f.type = get_args(argc, argv[1])) == E_NULL)
		KTHXBYE;
	f.mlx = ftx_init(&mlx_stack);
	ftx_winctor(f.mlx, WIN_X, WIN_Y, WIN_TITLE);
	ftx_imgctor(f.mlx, WIN_X, WIN_Y);
	key(X_KEY_SPACE, &f);
	mlx_hook(f.mlx->win[0], X_KEYPRESS, X_KEYPRESS_MASK, key, &f);
	mlx_hook(f.mlx->win[0], X_BUTTONPRESS, X_BUTTONPRESS_MASK, button, &f);
	mlx_hook(f.mlx->win[0], X_MOTIONNOTIFY, X_POINTERMOTION_MASK, motion, &f);
	mlx_loop(f.mlx->mlx);
	KTHXBYE;
}
