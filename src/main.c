/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:41:34 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/09 09:11:11 by nfinkel          ###   ########.fr       */
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
				if (z.r * z.r + z.i * z.i >= 4)
					break ;
			}
			z.color += it * 11 << 16;
			ftx_buffpixel(_MLX_IMG, x, y, (it == it_max ? _BLACK : z.color));
		}
	ftx_showimg(mlx, 0, 0);
}

static t_info	*init_info(t_info *info)
{
	info->x0 = -2.1;
	info->x1 = 0.6;
	info->y0 = -1.2;
	info->y1 = 1.2;
	info->zoom = 400.0;
	GIMME(info);
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
	frac.info = init_info(&info_stack);
	frac.it = 100;
	mlx_hook(frac.mlx->win[0], X_KEYPRESS, X_KEYPRESS_MASK,\
		(int (*)())key_hook, &frac);
	mlx_hook(frac.mlx->win[0], X_BUTTONPRESS, X_BUTTONMOTION_MASK,\
		(int (*)())mouse_hook, &frac);
	mlx_loop(frac.mlx->mlx);
	KTHXBYE;
}
