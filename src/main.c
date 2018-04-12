/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:41:34 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/12 15:37:10 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define WIN_TITLE "fractol"

static const char	*g_usage =
{
	"usage: ./fractol <fractal>"
};

static const void	*g_f[] =
{
	NULL,
	NULL, //julia,
	mandelbrot
};

static t_type	get_args(int argc, const char *s)
{
	if (argc == 2)
	{
		if (ft_strequ(s, "Mandelbrot"))
			GIMME(E_MANDEL);
		else if (ft_strequ(s, "Julia"))
			GIMME(E_JULIA);
	}
	ft_printf("%s\n", g_usage);
	GIMME(E_NULL);
}

void	*mandelbrot(t_info *f)
{
	double		tmp;
	double		y;
	t_complex	z;
	uint16_t	it;

	while (++f->x < f->x_max && (y = -1))
		while (++y < WIN_Y && (it = -1))
		{
			z.cr = f->x / f->zoom + f->x_scale;
			z.ci = y / f->zoom + f->y_scale;
			z.r = 0;
			z.i = 0;
			while (++it < f->it && z.r * z.r + z.i * z.i <= 4)
			{
				tmp = z.r;
				z.r = z.r *z.r - z.i * z.i + z.cr;
				z.i = 2 * z.i * tmp + z.ci;
			}
			z.color = it * 11 << 16;
			ftx_buffpixel(f->mlx->img[0], f->x, y,\
				(it == f->it ? _BLACK : z.color));
		}
	pthread_exit(NULL);
}

static void	init_info(t_info *f)
{
	f->it = 100;
	f->x_scale = -2.1;
	f->y_scale = -1.2;
	f->zoom = 400.0;
}

void	terminate(t_info *f)
{
	ftx_mlxdtor(f->mlx);
	exit(EXIT_SUCCESS);
}

int	output(t_info *f)
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
		pthread_create(th + k, NULL, (void *(*)(void *))g_f[f->type], info + k);
	}
	while (k--)
		pthread_join(th[k], NULL);
	ftx_showimg(f->mlx, 0, 0);
	KTHXBYE;
}

int	key(int key, t_info *f)
{
	if (key == X_KEY_ESCAPE)
		terminate(f);
	else if (key == X_KEY_W)
		f->y_scale += 0.1;
	else if (key == X_KEY_A)
		f->x_scale += 0.1;
	else if (key == X_KEY_S)
		f->y_scale -= 0.1;
	else if (key == X_KEY_D)
		f->x_scale -= 0.1;
	else if (key == X_KEY_MINUS)
		f->it -= (f->it < 5 ? f->it : 5);
	else if (key == X_KEY_EQUAL)
		f->it += (f->it < 2000 ? 5 : 0);
	GIMME(output(f));
}

int	button(int button, int x, int y, t_info *f)
{
	(void)x;
	(void)y;
	if (button == X_SCROLL_DOWN)
		f->zoom *= 0.9;
	else if (button == X_SCROLL_UP)
		f->zoom *= 1.1;
	GIMME(output(f));
}

int motion(int x, int y, t_info *f) //TODO julia
{
	(void)x;
	(void)y;
	(void)f;
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
	init_info(&f);
	key(0, &f);
	mlx_hook(f.mlx->win[0], X_KEYPRESS, X_KEYPRESS_MASK, key, &f);
	mlx_hook(f.mlx->win[0], X_BUTTONPRESS, X_BUTTONPRESS_MASK, button, &f);
	mlx_hook(f.mlx->win[0], X_MOTIONNOTIFY, X_POINTERMOTION_MASK, motion, &f);
	mlx_loop(f.mlx->mlx);
	KTHXBYE;
}
