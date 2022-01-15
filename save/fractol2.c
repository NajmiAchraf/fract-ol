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

long double	get_pos(t_var *var, long double position, long double point)
{
	return (position + (point - THWT / 2) * var->scale);
}

long double	get_neg(t_var *var, long double position, long double point)
{
	return (position - (point - THWT / 2) * var->scale);
}

void	put_pixel_to_image(t_var *data, int x, int y, int color)
{
	data->dst = data->addr + (y * data->line_length + \
			x * (data->bits_per_pixel / 8));
	*(unsigned int *) data->dst = color;
}

void	reset_image(t_var *var)
{
	mlx_destroy_image(var->mlx, var->img);
	var->img = mlx_new_image(var->mlx, THWT, THWT);
	var->addr = mlx_get_data_addr(var->img, &var->bits_per_pixel,
			&var->line_length, &var->endian);
}


// int colors[10] = {0x00DFFF00, 0x00FFBF00, 0x00FF7F50, 0x00DE3163, 0x009FE2BF, 0x0040E0D0, 0x006495ED, 0x00CCCCFF, 0x00800080, 0x00008000};
int colors[16] = {0x0009012f, 0x00040449, 0x00000764, 0x000c2c8a, 0x001852b1, 0x00397dd1, 0x0086b5e5, 0x00d3ecf8, 0x00f1e9bf, 0x00f8c95f, 0x00ffaa00, 0x00cc8000, 0x00995700, 0x006a3403, 0x00421e0f, 0x0019071a};


void	show_image(t_var *var)
{
	mlx_put_image_to_window(var->mlx, var->win, var->img, 0, 0);
}

void	mandelbrot(t_var *var)
{
	var->cr = get_pos(var, var->org_re, var->re);
	var->ci = get_neg(var, var->org_im, var->im);
	var->zr = 0;
	var->zi = 0;
	var->k = -1;
	while (var->k++ < 500)
	{
		var->rtemp = var->zr * var->zr - var->zi * var->zi;
		var->zi = 2 * var->zr * var->zi + var->ci;
		var->zr = var->rtemp + var->cr;
		if (sqrt(var->zr * var->zr + var->zi * var->zi) > 2.)
		{
			put_pixel_to_image(var, var->re, var->im, colors[var->k % 16]);
			break ;
		}
	}
}

void	julia(t_var *var)
{
	var->cr = get_pos(var, var->org_re, var->re);
	var->ci = get_neg(var, var->org_im, var->im);
	var->zr = 0;
	var->zi = 0;
	var->k = -1;
	while (var->k++ < 500)
	{
		var->rtemp = var->zr * var->zr - var->zi * var->zi;
		var->zi = 2 * var->zr * var->zi + var->ci;
		var->zr = var->rtemp + var->cr;
		if (sqrt(var->zr * var->zr + var->zi * var->zi) > 2.)
		{
			put_pixel_to_image(var, var->re, var->im, colors[var->k % 16]);
			break ;
		}
	}
}

void	plot(t_var *var)
{
	var->re = -1;
	while (var->re++ < THWT - 1)
	{
		var->im = -1;
		while (var->im++ < THWT - 1)
		{
			if (var->func == 1)
				mandelbrot(var);
			else if (var->func == 2)
				julia(var);
		}
	}
	show_image(var);
}

void	init(t_var *var)
{
	var->step = 0.5;
	var->speed = 2;
	var->zoom = THWT / 4.;
	var->scale = 1./var->zoom;
	var->org_re = 0;
	var->org_im = 0;
	var->trs_re = 0;
	var->trs_im = 0;
}

void	show(t_var *var)
{
	var->scale = 1. / var->zoom;
	reset_image(var);
	mlx_clear_window(var->mlx, var->win);
	plot(var);
}

void	execute(int keycode, t_var *var)
{
	if (keycode == KY_LEFT)
		var->org_re -= var->step;
	else if (keycode == KY_RIGHT)
		var->org_re += var->step;
	else if (keycode == KY_DOWN)
		var->org_im -= var->step;
	else if (keycode == KY_UP)
		var->org_im += var->step;
	else if (keycode == KY_SPACE)
		init(var);
	else if (keycode == KY_PLUS && var->zoom > 0.)
	{
		var->zoom *= var->speed;
		var->step /= var->speed;
	}
	else if (keycode == KY_MINUS && var->zoom >= THWT / 4.)
	{
		var->zoom /= var->speed;
		var->step *= var->speed;
	}
	show(var);
}

int	bind(int keycode, t_var *var)
{
	if (keycode == KY_ESC)
	{
		mlx_destroy_window(var->mlx, var->win);
		exit(1);
	}
	else if (keycode == KY_LEFT || keycode == KY_RIGHT || keycode == KY_DOWN
		|| keycode == KY_UP || keycode == KY_SPACE || keycode == KY_PLUS
		|| keycode == KY_MINUS)
		execute(keycode, var);
	return (0);
}

int	mouse_position(int x, int y, t_var *var)
{
	var->x = x;
	var->y = y;
	/*
	var -> _originR = var -> originR + (x - THWT / 2) * var -> scaleFactor;
	var -> _originI = var -> originI - (y - THWT / 2) * var -> scaleFactor;
	*/
	return (0);
}

int	mouse_zoom(int keycode, int x, int y, t_var *var)
{
	if (keycode == CK_UP && var->zoom > 0.)
	{
		var->zoom *= var->speed;
		var->step /= var->speed;
	}
	else if (keycode == CK_DOWN && var->zoom >= THWT / 4.)
	{
		var->zoom /= var->speed;
		var->step *= var->speed;
	}
	if (keycode == CK_UP || keycode == CK_DOWN)
	{
		var->trs_re = get_pos(var, var->org_re, x);
		var->trs_im = get_neg(var, var->org_im, y);
		var->scale = 1. / var->zoom;
		var->org_re = get_neg(var, var->trs_re, x);
		var->org_im = get_pos(var, var->trs_im, y);
		show(var);
	}
	return (0);
}

int	xite(int keycode, t_var *var)
{
	exit(1);
	return (0);
}

int	main(int ac, char **av)
{
	t_var	var;

	if (ac >= 2)
	{
		var.func = ft_atoi(av[1]);
		init(&var);
		var.mlx = mlx_init();
		var.win = mlx_new_window(var.mlx, THWT, THWT, "FRACT'OL");
		var.img = mlx_new_image(var.mlx, THWT, THWT);
		var.addr = mlx_get_data_addr(var.img, &var.bits_per_pixel, &var.line_length,
				&var.endian);
		plot(&var);
		mlx_hook(var.win, 2, (1L << 0), bind, &var);
		// mlx_key_hook(var.win, bind, &var);

		mlx_hook(var.win, 17, (1L << 17), xite, &var);
		mlx_hook(var.win, 6, (1L << 6), mouse_position, &var);

		mlx_hook(var.win, 4, (1L << 2), mouse_zoom, &var);
		// mlx_mouse_hook(var.win, mouse_zoom, &var);

		mlx_loop(var.mlx);

	}
	return (0);
}
