/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2022/02/10 17:36:33 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"
void	show_help(void)
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

void	show_control(void)
{
	ft_putstr_fd("Controls :\n", 1);
	ft_putstr_fd("\tMove : Up / Down / Left / Right\n", 1);
	ft_putstr_fd("\tZoom : \n", 1);
	ft_putstr_fd("\t\tMouse Scroll by tracking the mouse pointer\n", 1);
	ft_putstr_fd("\t\tPlus (+) / Minus (-) by tracking the center\n", 1);
	ft_putstr_fd("\tReset view : Space\n", 1);
}
