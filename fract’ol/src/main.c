/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anajmi <anajmi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 14:35:42 by anajmi            #+#    #+#             */
/*   Updated: 2022/01/07 13:58:13 by anajmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fractol.h"

void	reset(t_var *var){
	if (var->mw >= THWT)
		var->mw = 0;
	else if (var->mw <= 0)
		var->mw = THWT;
	if (var->mh >= THWT)
		var->mh = 0;
	else if (var->mh <= 0)
		var->mh = THWT;
}

double redirect_y(t_var *var, double y){
	if (y > THWT)
		y -= THWT;
	return (y);
}
double redirect_x(t_var *var, double x){
	if (x > THWT)
		x -= THWT;
	return (x);
}

void	my_mlx_pixel_clear(t_var *var)
{
	char	*dst;
	for(int x = 0; x < THWT; x++){
		for(int y = 0; y < THWT; y++){
			dst = var->addr + (y * var->line_length + x * (var->bits_per_pixel / 8));
			*(unsigned int*)dst = 0x00000000;
		}
	}
}

void	my_mlx_pixel_put(t_var *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void pixel_put(t_var *var, double x, double y, int color)
{
	// mlx_pixel_put(var->mlx, var->win, redirect_x(var, x), redirect_y(var, y), color);
	if (x * var->zoom > THWT || y * var->zoom > THWT)
		return ;
	//my_mlx_pixel_put(var, redirect_x(var, x * var->zoom), redirect_y(var, y * var->zoom), color);
	my_mlx_pixel_put(var,  x * var->zoom, y * var->zoom, color);
}

int colors[10] = {0x00DFFF00, 0x00FFBF00, 0x00FF7F50, 0x00DE3163, 0x009FE2BF, 0x0040E0D0, 0x006495ED, 0x00CCCCFF, 0x00800080, 0x00008000};

void Mandle(t_var *var, double _Complex c, double _Complex t, int counter, int color)
{
	// // To eliminate out of bound values.
	// if (cabs(t) > 2) {
	// 	pixel_put(var,  (creal((c)) * var->height / 2 + var->width / 2),
	// 			  (cimag((c)) * var->height / 2 + var->height / 2),
	// 			  mlx_get_color_value(var->mlx, 255 * ((1 - cos(cabs(t) / cabs(c))) / 2)));// COLOR(128 - 128 * cabs(t) / cabs(c), 128 - 128 * cabs(t) / cabs(c), 128 - 128 * cabs(t) / cabs(c)));
	// 	// printf("%f + i%f\n", (creal((c)) * var->height / 2 + var->width / 2), (cimag((c)) * var->height / 2 + var->height / 2));
	// 	return ;
	// }
	// // To put about the end of the fractal,
	// // the higher the value of the counter,
	// // The more accurate the fractal is generated,
	// // however, higher values cause
	// // more processing time.
	// if (counter == 50) {
	// 	// pixel_put(var,  (creal((c)) * var->height / 2 + var->width / 2) ,
	// 	// 		  (cimag((c)) * var->height / 2 + var->height / 2) ,
	// 	// 		  128 * cabs(t) / cabs(c) + color);//COLOR(255 * (cabs((t * t)) / cabs((t - c) * c)), 0, 0));
	// 	return ;
	// }
	// // recursively calling Mandle with increased counter
	// // and passing the value of the squares of t into it.
	// Mandle(var, c, cpow(t, 2) + c, counter + 1, color);

	while (counter <= 100){
		t = cpow(t, 2) + c;
		if (cabs(t) > 2) {
			pixel_put(var,  (creal((c)) * THWT / 2 + THWT / 2),
					(cimag((c)) * THWT / 2 + THWT / 2), colors[counter % 10]);
					// mlx_get_color_value(var->mlx, 1000 * (( cos(cabs(t) / cabs(c))) / 2)));
			break;
		}
		counter++;
	}

	return ;
}

void func(t_var *var){
	mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw, var->mh);
	if (var->mw > 0)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw - THWT, var->mh);
	else if (var->mw < THWT)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw + THWT, var->mh);
	if (var->mh > 0)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw, var->mh - THWT);
	else if (var->mh < THWT)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw, var->mh + THWT);

	if (var->mw > 0 && var->mh > 0)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw - THWT, var->mh - THWT);
	else if (var->mw < THWT && var->mh < THWT)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw + THWT, var->mh + THWT);
	if (var->mw > 0 && var->mh < THWT)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw - THWT, var->mh + THWT);
	else if (var->mw < THWT && var->mh > 0)
		mlx_put_image_to_window(var->mlx, var->win, var->img, var->mw + THWT, var->mh - THWT);
}

void funcz(t_var *var){
	double x, y;
	long color;

	color = 0xC0D5A0;
	double _Complex t = 0;
	double _Complex c;
	int counter = 0;
	for (double x = -2; x < 2.0; x += 0.0015) {
		for (double y = -1; y < 1.0; y += 0.0015) {
			c = x + y * _Complex_I;
			Mandle(var, c, t, counter, color);
		}
	}
   func(var);
}

void funcmd0(t_var *var){
	double x, y;
	double _Complex t;
	double _Complex c;
	int counter;

	for (double x = -2; x < 2.0; x += 0.0015) {
       for (double y = -1; y < 1.0; y += 0.0015) {
			c = x + y * _Complex_I;
			counter = 0;
			t = 0;
			while (counter <= 100){
				t = cpow(t, 2) + c;
				if (cabs(t) > 2) {
					pixel_put(var,  (creal((c)) * THWT / 2 + THWT / 2),
							(cimag((c)) * THWT / 2 + THWT / 2), colors[counter % 10]);
					break;
				}
				counter++;
			}
		}
	}
   func(var);
}

void funcmd(t_var *var){
	double x, y;

	double scaleFactor = 0.007 ;
	double originR = 0;
	double originI = 0;

	for (int x = 0; x < THWT; x++) {
		for (int y = 0; y < THWT; y++) {
			double cr = originR + (x - THWT / 2) * scaleFactor;
			double ci = originI - (y - THWT / 2) * scaleFactor;
			double zr = 0;
			double zi = 0;
			for (int k = 0; k < 100; k++) {
				double _zr = zr * zr - zi * zi + cr;
				double _zi = 2 * zr * zi + ci;
				zr = _zr;
				zi = _zi;
				double dist = sqrt(zr * zr + zi * zi);
				//printf("%lf\n", dist);
				//printf("(x = %d) , (y = %d)\n", x, y);
				if (dist > 2) {
					pixel_put(var, x, y, colors[k % 10]);
					break;
				}
			}
		}
	}
   func(var);
}

/* void	mandelbrot_pthread(t_var *data)
{
	t_var		tab[120];
	pthread_t	t[120];
	int			i;

	i = 0;
	while (i < 120)
	{
		ft_memcpy((void*)&tab[i], (void*)data, sizeof(t_var));
		tab[i].y = 5 * i;
		tab[i].ymax = 5 * (i + 1);
		pthread_create(&t[i], NULL, funcmd, &tab[i]);
		i++;
	}
	while (i--)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
} */

/* void	mandel(t_var *var)
{
	double scaleFactor = 1 / 500;
	double originR = -0.128;
	double originI = 0.987;
	double tmp0;
	int z0 = -1;
	while (++z0 != 350000)
	{
		int x = z0 % 700;
		int y = z0 / 700;
		double c_i0 = originR + (x - var->width / 2) * scaleFactor;
		double c_r0 = originI - (y - var->height / 2) * scaleFactor;
		double z_r0 = 0;
		double z_i0 = 0;
		int i0 = 0;
		while (sqrt(z_r0 * z_r0 + z_i0 * z_i0) < 4 && i0 < 100)
		{
			tmp0 = z_r0;
			z_r0 = z_r0 * z_r0 - z_i0 * z_i0 + c_r0;
			z_i0 = 2 * tmp0 * z_i0 + c_i0;
			i0++;
		}
		if (i0 != 100)
				pixel_put(var, x, y, colors[i0 % 10]);
			// var->addr[y * 700 + x] = colors[i0 % 10] + i0 * 1248518;
	}
	func(var);
} */

int	bind(int keycode, t_var *var)
{
	mlx_clear_window(var->mlx, var->win);
	// my_mlx_pixel_clear(var);
	if (keycode == KY_LEFT)
		var->mw -= var->speed, printf("left %d\n", var->mw);
	else if (keycode == KY_RIGHT)
		var->mw += var->speed, printf("right %d\n", var->mw);
	else if (keycode == KY_DOWN)
		var->mh += var->speed, printf("down %d\n", var->mh);
	else if (keycode == KY_UP)
		var->mh -= var->speed, printf("up %d\n", var->mh);
	if (keycode == KY_LEFT || keycode == KY_RIGHT || keycode == KY_DOWN || keycode == KY_UP)
	{
		reset(var);
		mlx_clear_window(var->mlx, var->win);
		func(var);
	}
	else if (keycode == KY_SPACE){
		var->mw = 0, var->mh = 0, mlx_clear_window(var->mlx, var->win);
		func(var);
	}
	if (keycode == KY_PLUS)
		var->zoom += 0.3, printf("zoom plus %f\n", var->zoom);
	else if (keycode == KY_MINUS)
		var->zoom -= 0.3, printf("zoom minus %f\n", var->zoom);
	if (keycode == KY_PLUS || keycode == KY_MINUS)
	{
		my_mlx_pixel_clear(var);
		funcz(var);
	}
    if (keycode == 53)
	 {
		mlx_destroy_window(var->mlx, var->win), printf("destroy\n");
		exit(1);
	}
    printf("%d\n", keycode);
    return (0);
}

int	exitx(int keycode, t_var *var)
{
	exit(1);
	return (0);
}

int	main(void)
{
	t_var	var;

	var.mh = 0;
	var.mw = 0;
	var.speed = 50;
	var.zoom = 1;
	// var.height = var.width / 2;
	var.mlx = mlx_init();
	var.win = mlx_new_window(var.mlx, THWT, THWT, "FRACT'OL");
	var.img = mlx_new_image(var.mlx, THWT, THWT);
	var.addr = mlx_get_data_addr(var.img, &var.bits_per_pixel, &var.line_length,
			&var.endian);
	//funcz(&var);
	//funcmd0(&var);
	funcmd(&var);
	//mandel(&var);
	//mandelbrot_pthread(&var); 
	mlx_hook(var.win, 2, 1L << 0, bind, &var);
	mlx_hook(var.win, 17, 1L << 17, exitx, &var);
	mlx_loop(var.mlx);
}
