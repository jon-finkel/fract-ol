/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <nfinkel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 16:41:06 by nfinkel           #+#    #+#             */
/*   Updated: 2018/04/10 23:16:33 by nfinkel          ###   ########.fr       */
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

typedef struct	s_frac
{
	t_mlx		*mlx;
	t_type		type;
}				t_frac;

#endif
