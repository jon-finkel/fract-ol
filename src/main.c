/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:41:34 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/11 23:19:54 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define WIN_TITLE "fractol"

static const char	*g_usage =
{
	"usage: ./fractol <fractal>"
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

void	*mandel(t_info *info)
{
	double		tmp;
	double		y;
	t_complex	z;
	uint16_t	it;

	while (++info->x < info->x_max && (y = -1))
		while (++y < WIN_Y)
		{
			ft_memset(&z, '\0', sizeof(t_complex));
			z.cr = info->x / info->zoom + info->x_scale;
			z.ci = y / info->zoom + info->y_scale;
			it = -1;
			while (++it < info->it && z.r * z.r + z.i * z.i <= 4)
			{
				tmp = z.r;
				z.r = z.r *z.r - z.i * z.i + z.cr;
				z.i = 2 * z.i * tmp + z.ci;
			}
			z.color += it * 11 << 16;
			ftx_buffpixel(info->mlx->img[0], info->x, y, (it == info->it ? _BLACK : z.color));
		}
	pthread_exit(NULL);
}

static t_info	*init_info(t_info *info, t_mlx *mlx)
{
	info->it = 100;
	info->mlx = mlx;
	info->x_scale = -2.1;
	info->y_scale = -1.2;
	info->zoom = 400.0;
	GIMME(info);
}

void	terminate(t_frac *f)
{
	ftx_mlxdtor(f->mlx);
	exit(EXIT_SUCCESS);
}

int	output(t_info *info)
{
	int			k;
	pthread_t	threads[THREADS];
	t_info		f[THREADS];

	ftx_clearwin(info->mlx);
	k = -1;
	while (++k < THREADS)
	{
		f[k] = *info;
		f[k].x = ((WIN_X / THREADS) * k) - 1;
		f[k].x_max = (WIN_X / THREADS) * (k + 1) + 1;
		pthread_create(threads + k, NULL, (void *(*)(void *))mandel, f + k);
	}
	while (k--)
		pthread_join(threads[k], NULL);
	ftx_showimg(info->mlx, 0, 0);
	KTHXBYE;
}

int	key_hook(int key, t_frac *f)
{
	if (key == X_KEY_ESCAPE)
		terminate(f);
	GIMME(output(f->info));
}

int	mouse_hook(int button, int x, int y, t_frac *f)
{
	(void)x;
	(void)y;
	if (button == X_SCROLL_DOWN)
		f->info->zoom -= 5;
	else if (button == X_SCROLL_UP)
		f->info->zoom += 5;
	GIMME(output(f->info));
}

int				main(int argc, const char *argv[])
{
	t_frac	f;
	t_info	info_stack;
	t_mlx	mlx_stack;

	if ((f.type = get_args(argc, argv[1])) == E_NULL)
		KTHXBYE;
	f.mlx = ftx_init(&mlx_stack);
	ftx_winctor(f.mlx, WIN_X, WIN_Y, WIN_TITLE);
	ftx_imgctor(f.mlx, WIN_X, WIN_Y);
	f.info = init_info(&info_stack, f.mlx);
	mlx_hook(f.mlx->win[0], X_KEYPRESS, X_KEYPRESS_MASK, key_hook, &f);
	mlx_hook(f.mlx->win[0], X_BUTTONPRESS, X_BUTTONPRESS_MASK, mouse_hook, &f);
	key_hook(0, &f);
	mlx_loop(f.mlx->mlx);
	KTHXBYE;
}
