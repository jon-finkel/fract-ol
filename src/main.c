/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:41:34 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/08 21:16:31 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#define WIN_X 1200
#define WIN_Y 900
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

int				main(int argc, const char *argv[])
{
	t_frac		frac;
	t_mlx		mlx_stack;

	if ((frac.type = get_args(argc, argv[1])) == E_NULL)
		KTHXBYE;
	frac.mlx = ftx_init(&mlx_stack);
	frac.it = 50;
	ftx_winctor(frac.mlx, WIN_X, WIN_Y, WIN_TITLE);
	ftx_imgctor(frac.mlx, WIN_X, WIN_Y);
	mlx_hook(frac.mlx->win[0], X_KEYPRESS, X_KEYPRESS_MASK, key_hook, &frac);
	mlx_loop(frac.mlx->mlx);
	KTHXBYE;
}
