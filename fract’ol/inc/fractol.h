/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:31:49 by anajmi            #+#    #+#             */
/*   Updated: 2022/01/06 20:59:28 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../Libft/libft.h"
# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include <complex.h>
# include <stdlib.h>
# include <pthread.h>

/*
keyboard binds
*/

# define KY_ESC 53
# define KY_SPACE 49

# define THWT 700

# ifdef __LINUX__
#  define KY_LEFT 65361
#  define KY_RIGHT 65362
#  define KY_DOWN 65363
#  define KY_UP 65364

# elif __APPLE__
#  define KY_LEFT 123
#  define KY_RIGHT 124
#  define KY_DOWN 125
#  define KY_UP 126
#  define KY_PLUS 69
#  define KY_MINUS 78
# endif

typedef struct s_var
{
	void	*mlx;
	void	*win;
	int		mw;
	int		mh;
	int		speed;
	double	zoom;
	void	*img;
	char	*addr;
	int		y;
	int		ymax;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_var;


#endif