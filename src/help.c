/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2022/02/13 13:42:09 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	show_help(void)
{
	ft_putstr("----------------------------------------------");
	ft_putstr("---------------------------\n");
	ft_putstr("| Usage : ./fractol [Window size] [Iteration]");
	ft_putstr(" [Fractal number] {Option} |\n");
	ft_putstr("----------------------------------------------");
	ft_putstr("---------------------------\n");
	ft_putstr("|\tWindow size :\t\t\t\t\t\t\t|\n");
	ft_putstr("|\t\tFrom 200 to 1000\t\t\t\t\t|\n");
	ft_putstr("|\tIteration :\t\t\t\t\t\t\t|\n");
	ft_putstr("|\t\tFrom 50 to 500\t\t\t\t\t\t|\n");
	ft_putstr("|\tFractal number :\t\t\t\t\t\t|\n");
	ft_putstr("|\t\t1 : Mandelbrot\t\t\t\t\t\t|\n");
	ft_putstr("|\t\t2 : Julia set manual input\t\t\t\t|\n");
	ft_putstr("|\t\t\tOption :\t\t\t\t\t|\n");
	ft_putstr("|\t\t\t\t[x] Real axe coordinate\t\t\t|\n");
	ft_putstr("|\t\t\t\t[z] Complex axe coordinate\t\t|\n");
	ft_putstr("|\t\t3 : Mandelbrot^n\t\t\t\t\t|\n");
	ft_putstr("|\t\t\tOption : [n] From 3 to 5\t\t\t|\n");
	ft_putstr("|\t\t4 : Julia set auto-mouse input\t\t\t\t|\n");
	ft_putstr("----------------------------------------------");
	ft_putstr("--------------------------\n");
}

void	show_control(void)
{
	ft_putstr("----------------------------------------------");
	ft_putstr("---------------------------\n");
	ft_putstr("| Controls :\t\t\t\t\t\t\t\t|\n");
	ft_putstr("|\tMove : Up / Down / Left / Right\t\t\t\t\t|\n");
	ft_putstr("|\tZoom :\t\t\t\t\t\t\t\t|\n");
	ft_putstr("|\t\tMouse Scroll by tracking the mouse pointer\t\t|\n");
	ft_putstr("|\t\tPlus (+) / Minus (-) by tracking the center\t\t|\n");
	ft_putstr("|\tColor : C\t\t\t\t\t\t\t|\n");
	ft_putstr("|\tReset values : Space\t\t\t\t\t\t|\n");
	ft_putstr("----------------------------------------------");
	ft_putstr("---------------------------\n");
}
