/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2022/02/10 18:02:12 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

long double	get_pos(t_var *var, long double position, long double point)
{
	return (position + (point - var->wtht / 2) * var->scale);
}

long double	get_neg(t_var *var, long double position, long double point)
{
	return (position - (point - var->wtht / 2) * var->scale);
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
	var->col = 1;
	var->zoom = var->wtht / 4.;
	var->scale = 1. / var->zoom;
	var->org_re = 0;
	var->org_im = 0;
	var->trs_re = 0;
	var->trs_im = 0;
}
