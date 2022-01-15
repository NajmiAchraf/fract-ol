/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2022/01/11 02:11:55 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	my_mlx_pixel_put(t_var *data, int x, int y, int color)
{
	data -> dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)data -> dst = color;
}

void	my_mlx_pixel_clear(t_var *var)
{
	var -> re = -1;
	while (var -> re++ < THWT - 1)
	{
		var -> im = -1;
		while (var -> im++ < THWT - 1)
		{
			my_mlx_pixel_put(var,  var -> re, var -> im, 0x00000000); ;
		}
	}
}

void pixel_put(t_var *var, double x, double y, int color)
{
	my_mlx_pixel_put(var,  x, y, color);
}

// int colors[10] = {0x00DFFF00, 0x00FFBF00, 0x00FF7F50, 0x00DE3163, 0x009FE2BF, 0x0040E0D0, 0x006495ED, 0x00CCCCFF, 0x00800080, 0x00008000};
int colors[16] = {0x0019071a, 0x0009012f, 0x00040449, 0x00000764, 0x000c2c8a, 0x001852b1, 0x00397dd1, 0x0086b5e5, 0x00d3ecf8, 0x00f1e9bf, 0x00f8c95f, 0x00ffaa00, 0x00cc8000, 0x00995700, 0x006a3403, 0x00421e0f};


void func(t_var *var){
	mlx_put_image_to_window(var->mlx, var->win, var->img, 0, 0);
}

void	funcmd(t_var *var)
{
	int n = 2;
	var -> re = -1;
	while (var -> re++ < THWT - 1)
	{
		var -> im = -1;
		while (var -> im++ < THWT - 1)
		{
			var -> cr = var -> org_re + (var -> re - THWT / 2) * var -> scale;
			var -> ci = var -> org_im - (var -> im - THWT / 2) * var -> scale;
			var -> zr = var -> x;
			var -> zi = var -> y;
			var -> k = -1;
			while (var -> k++ < 100)
			{
				// var -> rtemp = var -> zr * var -> zr - var -> zi * var -> zi;
				// var -> zi = 2 * var -> zr * var -> zi + var -> ci;
				// var -> zr = var -> rtemp + var -> cr;

				var -> rtemp = (var -> zr * var -> zr + var -> zi * var -> zi) * (n / 2) * cos(n * atan2(var -> zi, var -> zr)) + var -> cr;
				var -> zi = (var -> zr * var -> zr + var -> zi * var -> zi) * (n / 2) * sin(n * atan2(var -> zi, var -> zr)) + var -> ci;
				var -> zr = var -> rtemp;

				var -> dist = sqrt(var -> zr * var -> zr + var -> zi * var -> zi);
				if (var -> dist > 2)
				{
					pixel_put(var, var -> re, var -> im, colors[var -> k % 16]);
					break;
				}
			}
		}
	}
	func(var);
}

void	init(t_var *var)
{
	var -> speed = 0.5;
	var -> zoom = THWT / 4.;
	var -> scale = 1./var->zoom;
	var -> org_re = 0;
	var -> org_im = 0;
	var -> trs_re = 0;
	var -> trs_im = 0;
	var -> x = 0, var -> y = 0;
}

int	bind(int keycode, t_var *var)
{
	if (keycode == KY_LEFT)
		var -> org_re -= var -> speed, printf("left %Lg\n", var -> org_re);
	else if (keycode == KY_RIGHT)
		var -> org_re += var -> speed, printf("right %Lg\n", var -> org_re);
	else if (keycode == KY_DOWN)
		var -> org_im -= var -> speed, printf("down %Lg\n", var -> org_im);
	else if (keycode == KY_UP)
		var -> org_im += var -> speed, printf("up %Lg\n", var -> org_im);
	printf("R = %Lg | I = %Lg\n", var -> org_re, var -> org_im);
	if (keycode == KY_LEFT || keycode == KY_RIGHT || keycode == KY_DOWN || keycode == KY_UP)
	{
		my_mlx_pixel_clear(var);
		mlx_clear_window(var->mlx, var->win);
		funcmd(var);
	}
	else if (keycode == KY_SPACE){
		init(var);
		my_mlx_pixel_clear(var);
		mlx_clear_window(var->mlx, var->win);
		funcmd(var);
	}
	if (keycode == KY_PLUS && var -> zoom > 0.)
		var->zoom *= 2, var -> speed /= 2, printf("zoom plus %Lg\n", var->zoom);
	else if (keycode == KY_MINUS && var -> zoom >= THWT / 4.)
		var->zoom /= 2, var -> speed *= 2, printf("zoom minus %Lg\n", var->zoom);
	if (keycode == KY_PLUS || keycode == KY_MINUS)
	{
		var -> scale = 1. / var->zoom;
		var -> org_re = var -> trs_re - (var -> x - THWT / 2) * var -> scale;
		var -> org_im = var -> trs_im + (var -> y - THWT / 2) * var -> scale;

		var -> trs_re = var -> org_re + (var -> x - THWT / 2) * var -> scale;
		var -> trs_im = var -> org_im - (var -> y - THWT / 2) * var -> scale;
		
		my_mlx_pixel_clear(var);
		mlx_clear_window(var->mlx, var->win);
		funcmd(var);
	}
    if (keycode == 53)
	 {
		mlx_destroy_window(var->mlx, var->win), printf("destroy\n");
		exit(1);
	}
    printf("%d\n", keycode);
    return (0);
}

int	xite(int keycode, t_var *var)
{
	exit(1);
	return (0);
}

int	mouse_position(int x, int y, t_var *var)
{
	// var -> x = x, var -> y = y;
	// var -> _originR = var -> originR + (x - THWT / 2) * var -> scaleFactor;
	// var -> _originI = var -> originI - (y - THWT / 2) * var -> scaleFactor;

	var -> x = (-(x - THWT / 2.)*4.) / (THWT/2.), var -> y = ((y - THWT / 2.)*4.)/ (THWT/2.);
	// printf("x = %Lg | y = %Lg\n", var -> x, var -> y);
	my_mlx_pixel_clear(var);
	mlx_clear_window(var->mlx, var->win);
	funcmd(var);
	// printf("R = %Lg | I = %Lg\n", var -> _originR, var -> _originI);
	return (0);
}

int	mouse_zoom(int keycode, t_var *var)
{
	printf("%d\n", keycode);
	// if (keycode == CK_UP && var -> zoom > 0.)
	// 	var->zoom *= 2, var -> speed /= 2, printf("zoom plus %Lg\n", var->zoom);
	// else if (keycode == CK_DOWN && var -> zoom >= THWT / 4.)
	// 	var->zoom /= 2, var -> speed *= 2, printf("zoom minus %Lg\n", var->zoom);
	// if (keycode == CK_UP || keycode == CK_DOWN)
	// {
	// 	var -> scaleFactor = 1. / var->zoom;
	// 	var -> originR = var -> _originR - (var -> x - THWT / 2) * var -> scaleFactor;
	// 	var -> originI = var -> _originI + (var -> y - THWT / 2) * var -> scaleFactor;

	// 	var -> _originR = var -> originR + (var -> x - THWT / 2) * var -> scaleFactor;
	// 	var -> _originI = var -> originI - (var -> y - THWT / 2) * var -> scaleFactor;
		
	// 	my_mlx_pixel_clear(var);
	// 	mlx_clear_window(var->mlx, var->win);
	// 	funcmd(var);
	// }
	return (0);
}

int	main(void)
{
	t_var	var;

	init(&var);
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, THWT, THWT, "FRACT'OL");
	var.img = mlx_new_image(var.mlx, THWT, THWT);
	var.addr = mlx_get_data_addr(var.img, &var.bits_per_pixel, &var.line_length,
			&var.endian);
	funcmd(&var);
	mlx_hook(var.win, 2, 1L << 0, bind, &var);
	// mlx_key_hook(var.win, bind, &var);

	mlx_hook(var.win, 17, 1L << 17, xite, &var);
	mlx_hook(var.win, 6, 1L << 6, mouse_position, &var);

	mlx_hook(var.win, 4, 1L << 2, mouse_zoom, &var);
	// mlx_mouse_hook(var.win, mouse_zoom, &var);

	mlx_loop(var.mlx);
}
