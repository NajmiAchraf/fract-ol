/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3manimg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2021/12/29 03:14:42 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdlib.h>

typedef struct s_var
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	int		mw;
	int		mh;
	int		speed;
	double	zoom;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_var;

void	reset(t_var *var){
	if (var->mw >= var->width)
		var->mw = 0;
	else if (var->mw <= 0)
		var->mw = var->width;
	if (var->mh >= var->height)
		var->mh = 0;
	else if (var->mh <= 0)
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

void	my_mlx_pixel_clear(t_var *var)
{
	char	*dst;
	for(int x = 0; x < var->width; x++){
		for(int y = 0; y < var->height; y++){
			dst = var->addr + (y * var->line_length + x * (var->bits_per_pixel / 8));
			*(unsigned int*)dst = 0x00000000;
		}
	}
}

void	my_mlx_pixel_put(t_var *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void pixel_put(t_var *var, double x, double y, int color)
{
	// mlx_pixel_put(var->mlx, var->win, redirect_x(var, x), redirect_y(var, y), color);
	// my_mlx_pixel_put(var, redirect_x(var, x * var->zoom), redirect_y(var, y * var->zoom), color);
	my_mlx_pixel_put(var,  x * var->zoom, y * var->zoom, color);
}

void Mandle(t_var *var, double _Complex c, double _Complex t, int counter, int color)
{
	// // To eliminate out of bound values.
	// if (cabs(t) > 2) {
	// 	pixel_put(var,  (creal((c)) * var->height / 2 + var->width / 2),
	// 			  (cimag((c)) * var->height / 2 + var->height / 2),
	// 			  mlx_get_color_value(var->mlx, 255 * ((1 - cos(cabs(t) / cabs(c))) / 2)));// COLOR(128 - 128 * cabs(t) / cabs(c), 128 - 128 * cabs(t) / cabs(c), 128 - 128 * cabs(t) / cabs(c)));
	// 	// printf("%f + i%f\n", (creal((c)) * var->height / 2 + var->width / 2), (cimag((c)) * var->height / 2 + var->height / 2));
	// 	return ;
	// }

	// // To put about the end of the fractal,
	// // the higher the value of the counter,
	// // The more accurate the fractal is generated,
	// // however, higher values cause
	// // more processing time.
	// if (counter == 50) {
	// 	// pixel_put(var,  (creal((c)) * var->height / 2 + var->width / 2) ,
	// 	// 		  (cimag((c)) * var->height / 2 + var->height / 2) ,
	// 	// 		  128 * cabs(t) / cabs(c) + color);//COLOR(255 * (cabs((t * t)) / cabs((t - c) * c)), 0, 0));
	// 	return ;
	// }

	// // recursively calling Mandle with increased counter
	// // and passing the value of the squares of t into it.
	// Mandle(var, c, cpow(t, 2) + c, counter + 1, color);

	while (counter <= 100){
		t = cpow(t, 2) + c;
		if (cabs(t) > 4) {
			pixel_put(var,  (creal((c)) * var->height / 2 + var->width / 2),
					(cimag((c)) * var->height / 2 + var->height / 2),
					mlx_get_color_value(var->mlx, 1000 * (( cos(cabs(t) / cabs(c))) / 2)));
			break;
		}
		counter++;
	}

	return ;
}

void func(t_var *var){
	mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw, var->mh);
	if (var->mw > 0)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw - var->width, var->mh);
	else if (var->mw < var->width)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw + var->width, var->mh);
	if (var->mh > 0)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw, var->mh - var->height);
	else if (var->mh < var->height)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw, var->mh + var->height);

	if (var->mw > 0 && var->mh > 0)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw - var->width, var->mh - var->height);
	else if (var->mw < var->width && var->mh < var->height)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw + var->width, var->mh + var->height);
	if (var->mw > 0 && var->mh < var->height)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw - var->width, var->mh + var->height);
	else if (var->mw < var->width && var->mh > 0)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw + var->width, var->mh - var->height);
}

void funcz(t_var *var){
	double x, y;
	long color;

	color = 0xC0D5A0;
	double _Complex t = 0;
	double _Complex c;
	int counter = 0;
	for (double x = -2; x < 2.0; x += 0.0015) {
       for (double y = -1; y < 1.0; y += 0.0015) {
           c = x + y * _Complex_I;
           Mandle(var, c, t, counter, color);
       }
   }
   func(var);
}

int	bind(int keycode, t_var *var)
{
	// mlx_clear_window(var->mlx, var->win);
	// my_mlx_pixel_clear(var);
	
    if (keycode == 65361)
        var->mw -= var->speed, printf("left %d\n", var->mw);
    else if (keycode == 65363)
        var->mw += var->speed, printf("right %d\n", var->mw);
    else if (keycode == 65364)
    	var->mh += var->speed, printf("down %d\n", var->mh);
    else if (keycode == 65362)
        var->mh -= var->speed, printf("up %d\n", var->mh);
    if (keycode == 65364 || keycode == 65363 || keycode == 65362 || keycode == 65361)
	{
		reset(var);
		mlx_clear_window(var->mlx, var->win);
		func(var);
	}
    else if (keycode == 32){
	    var->mw = 0, var->mh = 0, mlx_clear_window(var->mlx, var->win);
		func(var);
	}
	if (keycode == 65451)
		var->zoom += 0.1, printf("zoom plus %f\n", var->zoom);
	else if (keycode == 65453)
		var->zoom -= 0.1, printf("zoom minus %f\n", var->zoom);

    if (keycode == 65451 || keycode == 65453)
	{
		my_mlx_pixel_clear(var);
		funcz(var);
	}

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
	var.zoom = 1;
	var.width = 1000;
	var.height = var.width / 2;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, var.width, var.height, "FRACT'OL");
	var.img = mlx_new_image(var.mlx, var.width, var.height);
	var.addr = mlx_get_data_addr(var.img, &var.bits_per_pixel, &var.line_length,
								&var.endian);
	// double x, y;
	// long color;

	// color = 0xC0D5A0;
	// double _Complex t = 0;
	// double _Complex c;
	// int counter = 0;
	// for (double x = -2; x < 2; x += 0.0015) {
	// 	for (double y = -1; y < 1; y += 0.0015) {
	// 		c = x + y * _Complex_I;
	// 		Mandle(&var, c, t, counter, color);
	// 	}
	// }
	funcz(&var);
	// my_mlx_pixel_put(&var, 5, 5, 0x00FF0000);
	// mlx_put_image_to_window(var.mlx, var.win, var.img, 0, 0);
	
	mlx_hook(var.win, 2, 1L<<0, bind, &var);
	// mlx_hook(var.win, 3, 1L<<1, bind, &var);
	mlx_loop(var.mlx);
}

