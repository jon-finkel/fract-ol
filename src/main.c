/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:41:34 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/11 22:08:17 by nfinkel          ###   ########.fr       */
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

int	mandel(t_info *info)
{
	double		tmp;
	double		x;
	double		y;
	t_complex	z;
	uint16_t	it;

	x = -1;
	while (++x < info->x_max && (y = -1))
		while (++y < info->y_max && (it = -1))
		{
			ft_memset(&z, '\0', sizeof(t_complex));
			z.cr = x / info->zoom + info->x0;
			z.ci = y / info->zoom + info->y0;
			while (++it < info->it && z.r * z.r + z.i * z.i <= 4)
			{
				tmp = z.r;
				z.r = z.r *z.r - z.i * z.i + z.cr;
				z.i = 2 * z.i * tmp + z.ci;
			}
			z.color += it * 11 << 16;
			ftx_buffpixel(info->mlx->img[0], x, y, (it == info->it ? _BLACK : z.color));
		}
	ftx_showimg(info->mlx, 0, 0);
	KTHXBYE;
}

static t_info	*init_info(t_info *info, t_mlx *mlx)
{
	info->it = 100;
	info->mlx = mlx;
	info->x0 = -2.1;
	info->x1 = 0.6;
	info->y0 = -1.2;
	info->y1 = 1.2;
	info->zoom = 400.0;
	info->x_max = ROUND(2.7 * info->zoom);
	info->y_max = ROUND(2.4 * info->zoom);
	GIMME(info);
}

void	terminate(t_frac *frac)
{
	ftx_mlxdtor(frac->mlx);
	exit(EXIT_SUCCESS);
}

int	key_hook(int key, t_frac *frac)
{
	if (key == X_KEY_ESCAPE)
		terminate(frac);
/*	if (key == X_KEY_MINUS && frac->it)
		frac->it -= 10;
	else if (key == X_KEY_EQUAL && frac->it < _IT_MAX)
		frac->it += 10;*/
	GIMME(mandel(frac->info));
}

int				main(int argc, const char *argv[])
{
	t_frac	frac;
	t_info	info_stack;
	t_mlx	mlx_stack;

	if ((frac.type = get_args(argc, argv[1])) == E_NULL)
		KTHXBYE;
	frac.mlx = ftx_init(&mlx_stack);
	ftx_winctor(frac.mlx, WIN_X, WIN_Y, WIN_TITLE);
	ftx_imgctor(frac.mlx, WIN_X, WIN_Y);
	frac.info = init_info(&info_stack, frac.mlx);
	mlx_hook(frac.mlx->win[0], X_KEYPRESS, X_KEYPRESS_MASK, key_hook, &frac);
	mlx_loop(frac.mlx->mlx);
	KTHXBYE;
}
