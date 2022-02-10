/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2022/02/10 17:29:38 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	put_pixel_to_image(t_var *data, int x, int y, int color)
{
	data->dst = data->addr + (y * data->line_length + \
			x * (data->bits_per_pixel / 8));
	*(unsigned int *) data->dst = color;
}

void	reset_image(t_var *var)
{
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
