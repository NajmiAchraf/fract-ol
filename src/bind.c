/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2022/02/10 17:54:56 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

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
	else if (keycode == KY_C)
		color_change(var);
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

int	xite(void)
{
	exit(1);
	return (0);
}
