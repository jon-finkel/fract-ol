/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:41:06 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/17 20:03:03 by nfinkel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <libft.h>
# include <mlx.h>
# include <pthread.h>

# define THREADS (16)
# define WIN_X (1100)
# define WIN_Y (1100)

# define _BLACK 0xff000000

typedef enum	e_type
{
	E_MANDEL,
	E_JULIA,
	E_BURNING,
	E_TRICORN,
	E_FISH,
	E_FIREBROT,
	E_GALAXY,
	E_BUDDHA,
	E_TRIFORCE,
	E_VOID
}				t_type;

typedef struct	s_thumbnails
{
	int			x_begin;
	int			x_end;
	int			y_begin;
	int			y_end;
	int8_t		index;
}				t_thumbnails;

typedef struct	s_buddha
{
	double		x;
	double		y;
}				t_buddha;

typedef struct	s_info
{
	bool		lock;
	bool		orbital;
	bool		psych;
	bool		thumb_noise;
	double		x_scale;
	double		y_scale;
	double		zoom;
	int			x;
	int			x_max;
	int			y;
	int			y_max;
	t_complex	*julia;
	t_mlx		*mlx;
	t_type		type;
	t_type		*thumbnails;
	uint8_t		multi;
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint16_t	it;
	uint16_t	noise;
}				t_info;

struct			s_fractal
{
	const char	*name;
	void		*(*f)(t_info *);
};

t_type			*map_thumbnails(t_type *thumbnails, t_type current);
int				output(t_info *f, bool refresh_thumb);
int				output_data(t_info *f);
void			reset_info(t_info *f);
t_info			thumb_info(t_info *f, const int8_t k);

/*
** Events
*/
int				button(int button, int x, int y, t_info *f);
int				key(int key, t_info *f);
int				motion(int x, int y, t_info *f);
int				psych(t_info *f);

/*
** Fractals
*/
void			*burning(t_info *info);
void			*buddhabrot(t_info *info);
void			*firebrot(t_info *info);
void			*fish(t_info *info);
void			*galaxy(t_info *info);
void			*julia(t_info *info);
void			*mandelbrot(t_info *info);
void			*tricorn(t_info *info);
void			*triforce(t_info *info);

#endif
