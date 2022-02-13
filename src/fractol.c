/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2022/02/10 17:36:37 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

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
			put_pixel_to_image(var, var->re, var->im, colors()[var->k % 16]
				* var->col);
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
			put_pixel_to_image(var, var->re, var->im, colors()[var->k % 16]
				* var->col);
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
		var->zrtmp = pow((var->zr * var->zr + var->zi * var->zi), var->n * 0.5)
			* cos(var->n * atan2(var->zi, var->zr)) + var->cr;
		var->zi = pow(var->zr * var->zr + var->zi * var->zi, var->n * 0.5)
			* sin(var->n * atan2(var->zi, var->zr)) + var->ci;
		var->zr = var->zrtmp;
	}
	if (var->k == var->dpth + 1)
		put_pixel_to_image(var, var->re, var->im, 0x00000000);
	else
		put_pixel_to_image(var, var->re, var->im, colors()[var->k % 16]
			* var->col);
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
			put_pixel_to_image(var, var->re, var->im, colors()[var->k % 16]
				* var->col);
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
			if (var->nbfc == 1)
				mandelbrot(var);
			else if (var->nbfc == 2)
				julia_set(var);
			else if (var->nbfc == 3)
				mandelbrot_set(var);
			else if (var->nbfc == 4)
				julia_mouse(var);
		}
	}
	show_image(var);
}
