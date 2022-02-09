/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:31:49 by anajmi            #+#    #+#             */
/*   Updated: 2022/02/09 16:31:54 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../utils/utils.h"
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <complex.h>
# include <stdlib.h>

/*
keyboard binds
*/

# define KY_ESC 53

# define CK_LEFT 1
# define CK_UP 4
# define CK_DOWN 5

# ifdef __linux__
#  define KY_LEFT 65361
#  define KY_RIGHT 65363
#  define KY_DOWN 65364
#  define KY_UP 65362
#  define KY_PLUS 65451
#  define KY_MINUS 65453
#  define KY_SPACE 32
#  define CK_RIGHT 3
#  define CK_MIDDLE 2

# elif __APPLE__
#  define KY_LEFT 123
#  define KY_RIGHT 124
#  define KY_DOWN 125
#  define KY_UP 126
#  define KY_PLUS 69
#  define KY_MINUS 78
#  define KY_SPACE 49
#  define CK_RIGHT 2
#  define CK_MIDDLE 3
# endif

typedef struct s_var
{
	void			*mlx;
	void			*win;
	long double		speed;
	long double		zoom;
	long double		step;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	char			*dst;
	int				wtht;
	int				dpth;
	int				n;
	int				k;
	int				re;
	int				im;
	long double		x;
	long double		y;
	long double		scale;
	long double		org_re;
	long double		org_im;
	long double		trs_re;
	long double		trs_im;
	long double		cr;
	long double		ci;
	long double		zr;
	long double		zi;
	long double		zrtmp;
	long double		dist; //should delete
	int				func;
}					t_var;

#endif