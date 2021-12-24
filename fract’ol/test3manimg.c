/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2linimg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2021/12/23 18:02:18 by anajmi           ###   ########.fr       */
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
	
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
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

void	my_mlx_pixel_put(t_var *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void pixel_put(t_var *var, double x, double y)
{
	// mlx_pixel_put(var->mlx, var->win, redirect_x(var, x), redirect_y(var, y), color);
	my_mlx_pixel_put(var, redirect_x(var, x), redirect_x(var, y), 0x00FF0000);
}

void Mandle(t_var *var, double _Complex c, double _Complex t, int counter, int color)
{
	// To eliminate out of bound values.
	if (cabs(t) > 4) {
		//pixel_put(var,  creal(c) * var->height / 2 + var->width / 2 + var->mw, cimag(c) * var->height / 2 + var->height / 2 + var->mh, 128 - 128 * cabs(t) / cabs(c) + color);// COLOR(128 - 128 * cabs(t) / cabs(c), 128 - 128 * cabs(t) / cabs(c), 128 - 128 * cabs(t) / cabs(c)));
		return ;
	}

	// To put about the end of the fractal,
	// the higher the value of the counter,
	// The more accurate the fractal is generated,
	// however, higher values cause
	// more processing time.
	if (counter == 100) {
		pixel_put(var,  creal((c)) * var->height / 2 + var->width / 2 + var->mw,  cimag((c)) * var->height / 2 + var->height / 2 + var->mh);//COLOR(255 * (cabs((t * t)) / cabs((t - c) * c)), 0, 0));
		return ;
	}

	// recursively calling Mandle with increased counter
	// and passing the value of the squares of t into it.
	Mandle(var, c, cpow(t, 2) + c, counter + 1, color);

	return ;
}

void func(t_var *var){
    double theta;
	double N = 500;
    double x1,x2,x3,x4,y1,y2,y3,y4;
	double r = 150;
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
	mlx_put_image_to_window(var->mlx, var->win, var->img, 0, 0);
}

int	bind(int keycode, t_var *var)
{
    if (keycode == 123)
        var->mw -= var->speed, printf("left %d\n", var->mw);
    else if (keycode == 124)
        var->mw += var->speed, printf("right %d\n", var->mw);
    else if (keycode == 125)
    	var->mh += var->speed, printf("down %d\n", var->mh);
    else if (keycode == 126)
        var->mh -= var->speed, printf("up %d\n", var->mh);
	reset(var);
    if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
	{
		// mlx_clear_window(var->mlx, var->win);
		func(var);
	}

    else if (keycode == 49){
	    var->mw = 0, var->mh = 0;//, mlx_clear_window(var->mlx, var->win);
		func(var);
	}
		
    if (keycode == 53)
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
	var.width = 1920; 
	var.height = 1080;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, var.width, var.height, "FRACT'OL");
	var.img = mlx_new_image(var.mlx, var.width, var.height);
	var.addr = mlx_get_data_addr(var.img, &var.bits_per_pixel, &var.line_length,
								&var.endian);
	// my_mlx_pixel_put(&var, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(var.mlx, var.win, var.img, 0, 0);
	
	func(&var);
	mlx_hook(var.win, 2, 1L<<0, bind, &var);
	// mlx_hook(var.win, 3, 1L<<1, bind, &var);
	mlx_loop(var.mlx);
}

