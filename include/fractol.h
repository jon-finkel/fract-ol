/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:41:06 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/13 01:01:42 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libft.h>
# include <mlx.h>
# include <pthread.h>

# define THREADS (16)
# define WIN_X (1600)
# define WIN_Y (1200)

# define _BLACK 0xff000000
# define _WHITE 0xffffff

typedef enum	e_type
{
	E_BURNING,
	E_JULIA,
	E_MANDEL,
	E_NULL
}				t_type;

typedef struct	s_complex
{
	double		cr;
	double		ci;
	double		r;
	double		i;
}				t_complex;

typedef struct	s_info
{
	double		x_scale;
	double		y_scale;
	double		zoom;
	int			x;
	int			x_max;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	t_mlx		*mlx;
	t_type		type;
	uint16_t	it;
}				t_info;

struct			s_fractal
{
	const char	*name;
	void		*(*f)(t_info *);
};

int				output(t_info *f);
int				output_data(t_info *f);
void			terminate(t_info *f);

/*
** Events
*/
int				button(int button, int x, int y, t_info *f);
int				key(int key, t_info *f);
int				motion(int x, int y, t_info *f);

/*
** Fractals
*/
void			*burning(t_info *info);
void			*mandelbrot(t_info *info);

#endif
