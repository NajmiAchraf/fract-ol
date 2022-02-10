/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2022/02/09 21:45:54 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol1.h"

long double	get_pos(t_var *var, long double position, long double point)
{
	return (position + (point - var->wtht / 2) * var->scale);
}

long double	get_neg(t_var *var, long double position, long double point)
{
	return (position - (point - var->wtht / 2) * var->scale);
}

void	put_pixel_to_image(t_var *data, int x, int y, int color)
{
	data->dst = data->addr + (y * data->line_length + \
			x * (data->bits_per_pixel / 8));
	*(unsigned int *) data->dst = color;
}

void	reset_image(t_var *var)
{
	mlx_clear_window(var->mlx, var->win);
	mlx_destroy_image(var->mlx, var->img);
	var->img = mlx_new_image(var->mlx, var->wtht, var->wtht);
	var->addr = mlx_get_data_addr(var->img, &var->bits_per_pixel,
			&var->line_length, &var->endian);
}

int	*colors(void)
{
	static int	arr[16];

	arr[0] = 0x0009012f;
	arr[1] = 0x00040449;
	arr[2] = 0x00000764;
	arr[3] = 0x000c2c8a;
	arr[4] = 0x001852b1;
	arr[5] = 0x00397dd1;
	arr[6] = 0x0086b5e5;
	arr[7] = 0x00d3ecf8;
	arr[8] = 0x00f1e9bf;
	arr[9] = 0x00f8c95f;
	arr[10] = 0x00ffaa00;
	arr[11] = 0x00cc8000;
	arr[12] = 0x00995700;
	arr[13] = 0x006a3403;
	arr[14] = 0x00421e0f;
	arr[15] = 0x0019071a;
	return (arr);
}

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
	while (var->k++ < var->dpth)
	{
		var->zrtmp = var->zr * var->zr - var->zi * var->zi;
		var->zi = 2 * var->zr * var->zi + var->ci;
		var->zr = var->zrtmp + var->cr;
		if (var->zr * var->zr + var->zi * var->zi > 4)
		{
			put_pixel_to_image(var, var->re, var->im, colors()[var->k % 16]);
			break ;
		}
	}
}

void	julia_set(t_var *var)
{
	var->zr = get_pos(var, var->org_re, var->re);
	var->zi = get_neg(var, var->org_im, var->im);
	var->k = -1;
	while (var->k++ < var->dpth)
	{
		var->zrtmp = var->zr * var->zr - var->zi * var->zi;
		var->zi = 2 * var->zr * var->zi + var->ci;
		var->zr = var->zrtmp + var->cr;
		if (var->zr * var->zr + var->zi * var->zi > 4)
		{
			put_pixel_to_image(var, var->re, var->im, colors()[var->k % 16]);
			break ;
		}
	}
}

void	mandelbrot_set(t_var *var)
{
	var->cr = get_pos(var, var->org_re, var->re);
	var->ci = get_neg(var, var->org_im, var->im);
	var->zr = var->x;
	var->zi = var->y;
	var->k = -1;
	while ((var->zr * var->zr + var->zi * var->zi) < 4
		&& var->k++ < var->dpth)
	{
		var->zrtmp = (var->zr * var->zr + var->zi * var->zi) * (var->n * 0.5) * cos(var->n * atan2(var->zi, var->zr)) + var->cr;
		var->zi = (var->zr * var->zr + var->zi * var->zi) * (var->n * 0.5) * sin(var->n * atan2(var->zi, var->zr)) + var->ci;
		var->zr = var->zrtmp;
	}
	if (var->k == var->dpth + 1)
		put_pixel_to_image(var, var->re, var->im, 0x00000000);
	else
		put_pixel_to_image(var, var->re, var->im, colors()[var->k % 16]);
}

void	julia_mouse(t_var *var)
{
	var->cr = var->x;
	var->ci = var->y;
	var->zr = get_pos(var, var->org_re, var->re);
	var->zi = get_neg(var, var->org_im, var->im);
	var->k = -1;
	while (var->k++ < var->dpth)
	{
		var->zrtmp = var->zr * var->zr - var->zi * var->zi;
		var->zi = 2 * var->zr * var->zi + var->ci;
		var->zr = var->zrtmp + var->cr;
		if (var->zr * var->zr + var->zi * var->zi > 4)
		{
			put_pixel_to_image(var, var->re, var->im, colors()[var->k % 16]);
			break ;
		}
	}
}

void	plot(t_var *var)
{
	var->re = -1;
	while (var->re++ < var->wtht - 1)
	{
		var->im = -1;
		while (var->im++ < var->wtht - 1)
		{
			if (var->func == 1)
				mandelbrot(var);
			else if (var->func == 2)
				julia_set(var);
			else if (var->func == 3)
				mandelbrot_set(var);
			else if (var->func == 4)
				julia_mouse(var);
		}
	}
	show_image(var);
}

void	get_julia(t_var *var, char *s1, char *s2)
{
	var->cr = atof(s1);
	var->ci = atof(s2);
}

void	init(t_var *var)
{
	var->step = 0.5;
	var->speed = 2;
	var->zoom = var->wtht / 4.;
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
	else if (keycode == KY_MINUS && var->zoom >= var->wtht / 4.)
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
	var->x = get_pos(var, var->org_re, x);
	var->y = get_neg(var, var->org_im, y);
	show(var);
	return (0);
}

int	mouse_zoom(int keycode, int x, int y, t_var *var)
{
	if (keycode == CK_UP && var->zoom > 0.)
	{
		var->zoom *= var->speed;
		var->step /= var->speed;
	}
	else if (keycode == CK_DOWN && var->zoom >= var->wtht / 4.)
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

void	show_help()
{
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("Usage : || ./fractol [equi width height] [depth]", 1);
	ft_putstr_fd(" [fractal number] {option} ||\n", 1);
	ft_putstr_fd("\tequi width height :\n", 1);
	ft_putstr_fd("\t\tfrom 200 to 1000\n", 1);
	ft_putstr_fd("\tdepth :\n", 1);
	ft_putstr_fd("\t\tfrom 50 to 500\n", 1);
	ft_putstr_fd("\tfractal number :\n", 1);
	ft_putstr_fd("\t\t1 : Mandelbrot\n", 1);
	ft_putstr_fd("\t\t2 : Julia set manual input\n", 1);
	ft_putstr_fd("\t\t\toption : [x] real axe coordinate", 1);
	ft_putstr_fd(" [z] complex axe coordinate\n", 1);
	ft_putstr_fd("\t\t3 : Mandelbrot^n\n", 1);
	ft_putstr_fd("\t\t\toption : [n] from 3 to 5\n", 1);
	ft_putstr_fd("\t\t4 : Julia set auto-mouse input\n\n", 1);
}

void	show_control()
{
	ft_putstr_fd("Controls :\n", 1);
	ft_putstr_fd("\tMove : Up / Down / Left / Right\n", 1);
	ft_putstr_fd("\tZoom : \n", 1);
	ft_putstr_fd("\t\tMouse Scroll by tracking the mouse pointer\n", 1);
	ft_putstr_fd("\t\tPlus (+) / Minus (-) by tracking the center\n", 1);
	ft_putstr_fd("\tReset view : Space\n", 1);
}

int	check_args(t_var *var, int ac, char **av)
{
	var->func = ft_atoi(av[3]);
	if (1 <= var->func && var->func <= 4)
	{
		var->wtht = ft_atoi(av[1]);
		var->dpth = ft_atoi(av[2]);
		if ((var->func == 1 && ac == 4) || (var->func == 2 && ac == 6)
			|| (var->func == 3 && ac == 5) || (var->func == 4 && ac == 4))
			return (1);
		return (0);
	}
	return (0);
}

void	initialisation(t_var *var)
{
	init(var);
	var->mlx = mlx_init();
	var->win = mlx_new_window(var->mlx, var->wtht, var->wtht, "FRACT'OL");
	var->img = mlx_new_image(var->mlx, var->wtht, var->wtht);
	var->addr = mlx_get_data_addr(var->img, &var->bits_per_pixel,
			&var->line_length, &var->endian);
	mlx_hook(var->win, 2, (1L << 0), bind, var);
	mlx_hook(var->win, 17, (1L << 17), xite, var);
}

void	initialisation2(t_var *var, char **av)
{
	if (var->func == 2)
		get_julia(var, av[4], av[5]);
	else if (var->func == 3)
		var->n = ft_atoi(av[4]);
	if (var->func == 4)
		mlx_hook(var->win, 6, (1L << 6), mouse_position, var);
	else if (var->func != 4)
		mlx_hook(var->win, 4, (1L << 2), mouse_zoom, var);
}

int	main(int ac, char **av)
{
	t_var	var;
	int		pass;

	if (ac >= 4)
	{
		pass = check_args(&var, ac, av);
		if (pass == 1)
		{
			initialisation(&var);
			initialisation2(&var, av);
			show_control();
			plot(&var);
			mlx_loop(var.mlx);
		}
		else
			show_help();
	}
	else
		show_help();
	return (0);
}
