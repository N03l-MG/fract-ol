/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:40:31 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/22 17:18:16 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	re_draw_fractal(void *f)
{
	t_fractal	*fractal;
	double		time;
	double		update;

	fractal = (t_fractal *)f;
	time = mlx_get_time();
	update = 1 / 60.0;
	if (fractal->should_re_draw && (time - fractal->last_update_time) >= update)
	{
		if (fractal->name == JULIA)
		{
			draw_julia(fractal);
			draw_sliders(fractal);
		}
		else if (fractal->name == MANDELBROT || fractal->name == BURNING_SHIP)
			draw_mandelbrot(fractal);
		mlx_image_to_window(fractal->mlx_window, fractal->mlx_image, 0, 0);
		fractal->should_re_draw = false;
		fractal->last_update_time = time;
	}
}

void	render_fractal(t_fractal *fractal)
{
	fractal->mlx_window = mlx_init(WIDTH, HEIGHT, "fract-ol", false);
	if (!fractal->mlx_window)
		error_handler(ERR_WINDOW, fractal);
	fractal->mlx_image = mlx_new_image(fractal->mlx_window, WIDTH, HEIGHT);
	if (!fractal->mlx_image)
		error_handler(ERR_IMAGE, fractal);
	fractal->image_data = (unsigned char *)fractal->mlx_image->pixels;
	if (!fractal->image_data)
		error_handler(ERR_DATA, fractal);
	if (fractal->name == JULIA)
	{
		draw_julia(fractal);
		draw_sliders(fractal);
	}
	else if (fractal->name == MANDELBROT || fractal->name == BURNING_SHIP)
		draw_mandelbrot(fractal);
	mlx_image_to_window(fractal->mlx_window, fractal->mlx_image, 0, 0);
	mlx_cursor_hook(fractal->mlx_window, mouse_callback, fractal);
	mlx_scroll_hook(fractal->mlx_window, scroll_callback, fractal);
	mlx_key_hook(fractal->mlx_window, key_callback, fractal);
	mlx_loop_hook(fractal->mlx_window, re_draw_fractal, fractal);
	mlx_loop(fractal->mlx_window);
	clean_stop(fractal);
}
