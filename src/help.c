/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2022/02/11 13:54:05 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	show_help(void)
{
	ft_putstr("\n");
	ft_putstr("Usage : || ./fractol [window size] [depth]");
	ft_putstr(" [fractal number] {option} ||\n");
	ft_putstr("\twindow size :\n");
	ft_putstr("\t\tfrom 200 to 1000\n");
	ft_putstr("\tdepth :\n");
	ft_putstr("\t\tfrom 50 to 500\n");
	ft_putstr("\tfractal number :\n");
	ft_putstr("\t\t1 : Mandelbrot\n");
	ft_putstr("\t\t2 : Julia set manual input\n");
	ft_putstr("\t\t\toption : [x] real axe coordinate");
	ft_putstr(" [z] complex axe coordinate\n");
	ft_putstr("\t\t3 : Mandelbrot^n\n");
	ft_putstr("\t\t\toption : [n] from 3 to 5\n");
	ft_putstr("\t\t4 : Julia set auto-mouse input\n\n");
}

void	show_control(void)
{
	ft_putstr("Controls :\n");
	ft_putstr("\tMove : Up / Down / Left / Right\n");
	ft_putstr("\tZoom : \n");
	ft_putstr("\t\tMouse Scroll by tracking the mouse pointer\n");
	ft_putstr("\t\tPlus (+) / Minus (-) by tracking the center\n");
	ft_putstr("\tColor : C\n");
	ft_putstr("\tReset values : Space\n");
}
