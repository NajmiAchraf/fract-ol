/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test0linpx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@studetnt.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 17:12:01 by anajmi            #+#    #+#             */
/*   Updated: 2021/12/27 20:01:30 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdlib.h>

double theta30(double x){
  double out=3.0*sqrt(14.0)/4.0*(5.0/3.0*pow(cos(x),3)-cos(x));
  return out;
}
double theta31(double x){
  double out=(sqrt(42))/(8)*sin(x)*(5*pow(cos(x),2)-1);
  return out;
}
double theta32(double x){
  double out=sqrt(105)/4*pow(sin(x),2)*cos(x);
  return out;
}
double theta33(double x){
  double out=(sqrt(70))/(8)*(pow(sin(x),3));
  return out;
}

typedef struct	s_var
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	int 	mw;
	int		mh;
	int		speed;
	int		zoom;
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

void func(t_var *var){
	double theta;
	double N = 500;
	double x1,x2,x3,x4,y1,y2,y3,y4;
	double r = 150 + var->zoom;
	double x, y, sy, x0 = 500 + var->mw, y0 = 500 + var->mh;
	long color;
	
	color = 0x00FF00FF;
	for(theta = 0; theta <= 2 * M_PI; theta = theta + (1 / N)){
		x1 = (theta30(theta) * theta30(theta) * cos(theta)) * r;
		x2 = (theta31(theta) * theta31(theta) * cos(theta)) * r;
		x3 = (theta32(theta) * theta32(theta) * cos(theta)) * r;
		x4 = (theta33(theta) * theta33(theta) * cos(theta)) * r;
		y1 = (theta30(theta) * theta30(theta) * sin(theta)) * r;
		y2 = (theta31(theta) * theta31(theta) * sin(theta)) * r;
		y3 = (theta32(theta) * theta32(theta) * sin(theta)) * r;
		y4 = (theta33(theta) * theta33(theta) * sin(theta)) * r;
		pixel_put(var, x1 + x0, y1 + y0, color);
		pixel_put(var, x2 + x0, y2 + y0, color);
		pixel_put(var, x3 + x0, y3 + y0, color);
		pixel_put(var, x4 + x0, y4 + y0, color);
	}
	for(y = y0 - r; y <= y0 + r; y = y + 0.1){
		x = sqrt(r * r - (y - y0) * (y - y0)) + x0;
		pixel_put(var, x, y, color);
	}
	for(y = y0 + r; y >= y0 - r; y = y - 0.1){
		x = -sqrt(r * r - (y - y0) * (y - y0)) + x0;
		pixel_put(var, x, y, color);
	}
	y = var->height;
	for(x = 0; x < var->width; x++){
		y--;
		pixel_put(var, x + x0, y + y0, color);
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
	if (keycode == 65451)
		var->zoom += 50, printf("zoom plus %d\n", var->zoom);
	else if (keycode == 65453)
		var->zoom -= 50, printf("zoom minus %d\n", var->zoom);
	if (keycode == 65364 || keycode == 65363 || keycode == 65362 || keycode == 65361 || keycode == 65451 || keycode == 65453)
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
	var.speed = 50;
	var.zoom = 0;
	var.width = 2200;
	var.height = var.width / 2;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, var.width, var.height, "FRACT'OL");

	func(&var);
	mlx_hook(var.win, 02, (1L<<0), bind, &var);
	// mlx_hook(var.win, 04, (1L<<2), bind, &var);
	// mlx_hook(var.win, 05, 1L<<3, bind, &var);
	// mlx_key_hook(var.win, bind, &var);
	// mlx_hook(var.win, 3, 1L<<1, bind, &var);
	mlx_loop(var.mlx);
}
