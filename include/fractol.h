/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:41:06 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/12 15:09:50 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libft.h>
# include <mlx.h>
# include <pthread.h>

# define THREADS (32)
# define WIN_X 1600
# define WIN_Y 1200

# define _IT_MAX 30000
# define _BLACK 0xff000000
# define _WHITE 0xffffff

typedef enum	e_type
{
	E_NULL,
	E_JULIA,
	E_MANDEL
}				t_type;

typedef struct	s_complex
{
	double		cr;
	double		ci;
	double		r;
	double		i;
	int			color;
}				t_complex;

typedef struct	s_info
{
	double		x_scale;
	double		y_scale;
	double		zoom;
	int			x;
	int			x_max;
	t_mlx		*mlx;
	t_type		type;
	uint16_t	it;
}				t_info;

void			*mandelbrot(t_info *info);

#endif
