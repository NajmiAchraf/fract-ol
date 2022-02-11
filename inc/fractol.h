/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:31:49 by anajmi            #+#    #+#             */
/*   Updated: 2022/02/11 14:50:37 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

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
# define KY_C 8

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
	long double		dist;
	int				nbfc;
	int				col;
}					t_var;
long double	get_pos(t_var *var, long double position, long double point);
long double	get_neg(t_var *var, long double position, long double point);
void		put_pixel_to_image(t_var *data, int x, int y, int color);
void		reset_image(t_var *var);
int			*colors(void);
void		color_change(t_var *var);
void		show_image(t_var *var);
void		mandelbrot(t_var *var);
void		julia_set(t_var *var);
void		mandelbrot_set(t_var *var);
void		julia_mouse(t_var *var);
void		plot(t_var *var);
void		get_julia(t_var *var, char *s1, char *s2);
void		init(t_var *var);
void		show(t_var *var);
void		execute(int keycode, t_var *var);
int			bind(int keycode, t_var *var);
int			mouse_position(int x, int y, t_var *var);
int			mouse_zoom(int keycode, int x, int y, t_var *var);
int			xite(void);
void		show_help(void);
void		show_control(void);
int			check_args(t_var *var, int ac, char **av);
void		initialisation(t_var *var);
void		initialisation2(t_var *var, char **av);

#endif