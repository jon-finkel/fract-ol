/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:41:34 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/18 12:28:42 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define BUFF_SIZE (128)
#define WIN_TITLE "Fract'ol, a fractal explorer, by Jon Finkel"
#define _DATA " -- DATA -- "
#define _PSY "PSYCH MODE ON!"
#define _WHITE 0xffffff
#define _P1 (f->type >= E_GALAXY ? 75 : 60)
#define _P2 (f->type >= E_GALAXY ? 90 : 75)
#define _P3 (f->type >= E_GALAXY ? 105 : 90)

static const struct s_fractal	g_fractal[E_VOID] =
{
	{"Mandelbrot", mandelbrot},
	{"Julia", julia},
	{"BurningShip", burning},
	{"Tricorn", tricorn},
	{"Fish", fish},
	{"Firebrot", firebrot},
	{"Galaxy", galaxy},
	{"Buddhabrot", buddhabrot},
	{"Triforce", triforce}
};

static t_type	get_args(int argc, const char *s)
{
	int		k;

	if (argc == 2 && (k = -1))
		while (++k < E_VOID)
			if (ft_strequ(s, g_fractal[k].name))
				GIMME(k);
	ft_printf("usage: ./fractol [ Mandelbrot | Julia | BurningShip | Tricorn | "\
		"Fish | Firebrot | Galaxy | Buddhabrot | Triforce ]\n");
	GIMME(E_VOID);
}

static int		output_thumbnails(t_info *f, bool refresh_thumb)
{
	int8_t		k;
	pthread_t	th[THREADS / 2];
	t_info		info[THREADS / 2];

	ftx_setimg(f->mlx, 1);
	if (refresh_thumb == false)
	{
		ftx_showimg(f->mlx, WIN_X, 0);
		KTHXBYE;
	}
	ftx_clearimg(f->mlx->img[1]);
	f->thumb_noise = true;
	k = -1;
	while (++k < THREADS / 2)
	{
		info[k] = thumb_info(f, k);
		pthread_create(th + k, NULL,\
			(void *(*)(void *))g_fractal[f->thumbnails[k]].f, info + k);
	}
	while (k--)
		pthread_join(th[k], NULL);
	f->thumb_noise = false;
	ftx_showimg(f->mlx, WIN_X, 0);
	KTHXBYE;
}

int				output(t_info *f, bool refresh_thumb)
{
	int8_t		k;
	pthread_t	th[THREADS];
	t_info		info[THREADS];

	ftx_setimg(f->mlx, 0);
	ftx_clearwin(f->mlx, 0);
	ftx_clearimg(f->mlx->img[0]);
	k = -1;
	while (++k < THREADS)
	{
		info[k] = *f;
		info[k].invert = true;
		info[k].x = ((WIN_X / THREADS) * k) - 1;
		info[k].y = -1;
		info[k].x_max = (WIN_X / THREADS) * (k + 1);
		info[k].y_max = WIN_Y;
		pthread_create(th + k, NULL, (void *(*)(void *))g_fractal[f->type].f,\
			info + k);
	}
	while (k--)
		pthread_join(th[k], NULL);
	ftx_showimg(f->mlx, 0, 0);
	GIMME(output_thumbnails(f, refresh_thumb));
}

int				output_data(t_info *f)
{
	char	buff[BUFF_SIZE];

	mlx_string_put(f->mlx->mlx, f->mlx->win[0], 0, 0, _WHITE, _DATA);
	ft_snprintf(buff, BUFF_SIZE, " FRAC: %s", g_fractal[f->type].name);
	mlx_string_put(f->mlx->mlx, f->mlx->win[0], 0, 15, _WHITE, buff);
	ft_snprintf(buff, BUFF_SIZE, " ZOOM: x%.f", WIN_X * f->zoom / 10000);
	mlx_string_put(f->mlx->mlx, f->mlx->win[0], 0, 30, _WHITE, buff);
	ft_snprintf(buff, BUFF_SIZE, " ITER: %hu", f->it);
	mlx_string_put(f->mlx->mlx, f->mlx->win[0], 0, 45, _WHITE, buff);
	if (f->type >= E_GALAXY
		&& ft_snprintf(buff, BUFF_SIZE, " NOIS: %.2f",\
		(double)f->it / (double)f->noise))
		mlx_string_put(f->mlx->mlx, f->mlx->win[0], 0, 60, _WHITE, buff);
	if (f->psych == false)
	{
		ft_snprintf(buff, BUFF_SIZE, " RED = %hhu", f->r);
		mlx_string_put(f->mlx->mlx, f->mlx->win[0], 0, _P1, _WHITE, buff);
		ft_snprintf(buff, BUFF_SIZE, " GRN = %hhu", f->g);
		mlx_string_put(f->mlx->mlx, f->mlx->win[0], 0, _P2, _WHITE, buff);
		ft_snprintf(buff, BUFF_SIZE, " BLU = %hhu", f->b);
		mlx_string_put(f->mlx->mlx, f->mlx->win[0], 0, _P3, _WHITE, buff);
	}
	else
		mlx_string_put(f->mlx->mlx, f->mlx->win[0], 950, 0, rand(), _PSY);
	KTHXBYE;
}

int				main(int argc, const char *argv[])
{
	t_complex	julia;
	t_info		f;
	t_mlx		mlx_stack;
	t_type		thumbnails[8];

	if ((f.type = get_args(argc, argv[1])) == E_VOID)
		KTHXBYE;
	f.mlx = ftx_init(&mlx_stack);
	f.julia = &julia;
	ftx_winctor(f.mlx, WIN_X + (WIN_X / 2), WIN_Y, WIN_TITLE);
	ftx_imgctor(f.mlx, WIN_X, WIN_Y);
	ftx_imgctor(f.mlx, WIN_X / 2, WIN_Y);
	f.thumbnails = map_thumbnails(thumbnails, f.type);
	key(X_KEY_SPACE, &f);
	mlx_hook(f.mlx->win[0], X_KEYPRESS, X_KEYPRESS_MASK, key, &f);
	mlx_hook(f.mlx->win[0], X_BUTTONPRESS, X_BUTTONPRESS_MASK, button, &f);
	mlx_hook(f.mlx->win[0], X_MOTIONNOTIFY, X_POINTERMOTION_MASK, motion, &f);
	mlx_loop_hook(f.mlx->mlx, psych, &f);
	mlx_loop(f.mlx->mlx);
	KTHXBYE;
}
