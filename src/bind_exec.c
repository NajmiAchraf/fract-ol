/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2022/02/10 17:31:53 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

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

void	color_change(t_var *var)
{
	if (var->col > 10)
		var->col = 1;
	else if (var->col > 0)
		var->col += 1;
	show(var);
}
