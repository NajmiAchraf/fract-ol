/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1manpx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2021/12/23 23:11:23 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdlib.h>

typedef struct	s_var
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	int 	mw;
	int		mh;
	int		speed;
}				t_var;

void reset(t_var *var){
	if (var->mw > (var->width - var->speed))
		var->mw = 0;
	else if (var->mw < var->speed)
		var->mw = var->width;
	if (var->mh > (var->height - var->speed))
		var->mh = 0;
	else if (var->mh < var->speed)
		var->mh = var->height;
}

double redirect_y(t_var *var, double y){
	if (y > var->height)
		y -= var->height;
	return (y);
}
double redirect_x(t_var *var, double x){
	if (x > var->width)
		x -= var->width;
	return (x);
}

void pixel_put(t_var *var, double x, double y, int color)
{
	mlx_pixel_put(var->mlx, var->win, redirect_x(var, x), redirect_y(var, y), color);
}

void Mandle(t_var *var, double _Complex c, double _Complex t, int counter, int color)
{
	// To eliminate out of bound values.
	if (cabs(t) > 2) {
		pixel_put(var,  creal((c)) * var->height / 2 + var->width / 2 + var->mw,
						cimag((c)) * var->height / 2 + var->height / 2 + var->mh,
						mlx_get_color_value(var->mlx, 255 * ((1 - cos(cabs(t) / cabs(c))) / 2)));// COLOR(128 - 128 * cabs(t) / cabs(c), 128 - 128 * cabs(t) / cabs(c), 128 - 128 * cabs(t) / cabs(c)));
		return ;
	}

	// To put about the end of the fractal,
	// the higher the value of the counter,
	// The more accurate the fractal is generated,
	// however, higher values cause
	// more processing time.
	if (counter == 20) {
		pixel_put(var,  creal((c)) * var->height / 2 + var->width / 2 + var->mw,
						cimag((c)) * var->height / 2 + var->height / 2 + var->mh,
						128 * cabs(t) / cabs(c) + color);//COLOR(255 * (cabs((t * t)) / cabs((t - c) * c)), 0, 0));
		return ;
	}

	// recursively calling Mandle with increased counter
	// and passing the value of the squares of t into it.
	Mandle(var, c, cpow(t, 2) + c, counter + 1, color);

	return ;
}

void func(t_var *var){
	double x, y, sy, x0 = 500 + var->mw, y0 = 500 + var->mh;
	long color;

	color = 0xC0D5A0;
	double _Complex t = 0;
	double _Complex c;
	int counter = 0;
	for (double x = -2; x < 2; x += 0.0015) {
		for (double y = -1; y < 1; y += 0.0015) {
			c = x + y * _Complex_I;
			Mandle(var, c, t, counter, color);
		}
	}
}

int	bind(int keycode, t_var *var)
{
	if (keycode == 65361)
		var->mw -= var->speed, printf("left %d\n", var->mw);
	else if (keycode == 65363)
		var->mw += var->speed, printf("right %d\n", var->mw);
	else if (keycode == 65364)
		var->mh += var->speed, printf("down %d\n", var->mh);
	else if (keycode == 65362)
		var->mh -= var->speed, printf("up %d\n", var->mh);
	reset(var);
	if (keycode == 65364 || keycode == 65363 || keycode == 65362 || keycode == 65361)
	{
		mlx_clear_window(var->mlx, var->win);
		func(var);
	}

	else if (keycode == 32)
		var->mw = 0, var->mh = 0, mlx_clear_window(var->mlx, var->win), func(var);
	if (keycode == 65307)
	{
		mlx_destroy_window(var->mlx, var->win), printf("destroy\n");
		exit(1);
	}
	printf("%d\n", keycode);
	return (0);
}

int	main(void)
{
	t_var	var;

	var.mh = 0;
	var.mw = 0;
	var.speed = 200;
	var.width = 1500;
	var.height = var.width / 2;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, var.width, var.height, "FRACT'OL");

	func(&var);
	mlx_hook(var.win, 2, 1L<<0, bind, &var);
	// mlx_hook(var.win, 3, 1L<<1, bind, &var);
	mlx_loop(var.mlx);
}
