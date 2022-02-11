/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2022/02/10 18:45:34 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

int	check_args(t_var *var, int ac, char **av)
{
	var->nbfc = ft_atoi(av[3]);
	if (1 <= var->nbfc && var->nbfc <= 4)
	{
		var->wtht = ft_atoi(av[1]);
		if (var->wtht < 200)
			return (0);
		var->dpth = ft_atoi(av[2]);
		if (var->dpth < 50)
			return (0);
		if ((var->nbfc == 1 && ac == 4) || (var->nbfc == 2 && ac == 6)
			|| (var->nbfc == 3 && ac == 5) || (var->nbfc == 4 && ac == 4))
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
	if (var->nbfc == 2)
		get_julia(var, av[4], av[5]);
	else if (var->nbfc == 3)
		var->n = ft_atoi(av[4]);
	if (var->nbfc == 4)
		mlx_hook(var->win, 6, (1L << 6), mouse_position, var);
	else if (var->nbfc != 4)
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
