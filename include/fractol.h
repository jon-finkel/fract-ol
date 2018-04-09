/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:41:06 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/09 09:28:43 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libft.h>
# include <mlx.h>
# include <pthread.h>

# define THREADS (16)
# define WIN_X 1200
# define WIN_Y 900

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
	double		x0;
	double		x1;
	double		y0;
	double		y1;
	double		zoom;
	int			x_max;
	int			y_max;
}				t_info;

typedef struct	s_frac
{
	uint16_t	it;
	t_info		*info;
	t_mlx		*mlx;
	t_type		type;
}				t_frac;

void			key_hook(int key, t_frac *frac);
void			mouse_hook(int key, int x, int y, t_frac *frac);
void			output(t_mlx *mlx, const t_info info, const uint16_t it_max);
void			terminate(t_frac *frac);

#endif
