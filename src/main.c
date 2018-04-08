/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:41:34 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/08 23:43:25 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define WIN_X 1080
#define WIN_Y 960
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

void			terminate(t_frac *frac)
{
	ftx_mlxdtor(frac->mlx);
	exit(EXIT_SUCCESS);
}

int				key_hook(int key, t_frac *frac)
{
	if (key == X_KEY_ESCAPE)
		terminate(frac);
	KTHXBYE;
}

void			output(t_mlx *mlx, const t_info f, const uint16_t it_max)
{
	double		tmp;
	double		x;
	double		y;
	t_complex	z;
	uint16_t	it;

	x = -1;
	while (++x < f.x_max && (y = -1))
		while (++y < f.y_max && (it = -1))
		{
			ft_memset(&z, '\0', sizeof(t_complex));
			z.cr = x / f.zoom + f.x0;
			z.ci = y / f.zoom + f.y0;
			while (++it < it_max)
			{
				tmp = z.r;
				z.r = z.r *z.r - z.i * z.i + z.cr;
				z.i = 2 * z.i * tmp + z.ci;
				z.color = it * 105 + (it * 60 << 8) + (it * 98 << 16);
				if (z.r * z.r + z.i * z.i >= 4)
					break ;
			}
			ftx_buffpixel(_MLX_IMG, x, y, (it == it_max ? _BLACK : z.color));
		}
	ftx_showimg(mlx, 0, 0);
}

int				main(int argc, const char *argv[])
{
	t_frac	frac;
	t_info	f;
	t_mlx	mlx_stack;

	if ((frac.type = get_args(argc, argv[1])) == E_NULL)
		KTHXBYE;
	frac.mlx = ftx_init(&mlx_stack);
	frac.it = 200;
	ftx_winctor(frac.mlx, WIN_X, WIN_Y, WIN_TITLE);
	ftx_imgctor(frac.mlx, WIN_X, WIN_Y);
	f.zoom = 400.0;
	f.x0 = -2.1;
	f.x1 = 0.6;
	f.y0 = -1.2;
	f.y1 = 1.2;
	f.x_max = ROUND((f.x1 - f.x0) * f.zoom);
	f.y_max = ROUND((f.y1 - f.y0) * f.zoom);
	output(frac.mlx, f, frac.it);
	mlx_hook(frac.mlx->win[0], X_KEYPRESS, X_KEYPRESS_MASK, key_hook, &frac);
	mlx_loop(frac.mlx->mlx);
	KTHXBYE;
}
