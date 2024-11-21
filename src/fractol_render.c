/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:40:31 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/21 17:51:05 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	get_color(int iterations)
{
	int	r;
	int	g;
	int	b;

	if (iterations == MAX_ITER)
		return (0x000000);
	r = (iterations * 10) % 256;
	g = (iterations * 1) % 256;
	b = (iterations * 3) % 256;
	return ((r << 16) | (g << 8) | b);
}

void	re_draw_fractal(void *f)
{
	t_fractal	*fractal;

	fractal = (t_fractal *)f;
	if (fractal->should_re_draw)
	{
		if (fractal->name == JULIA)
		{
			draw_julia(fractal);
			draw_sliders(fractal);
		}
		else
			draw_mandelbrot(fractal);
		mlx_image_to_window(fractal->mlx_window, fractal->mlx_image, 0, 0);
		fractal->should_re_draw = false;
	}
}

void	render_fractal(t_fractal *fractal)
{
	fractal->mlx_window = mlx_init(WIDTH, HEIGHT, "fract-ol", true);
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
	else if (fractal->name == MANDELBROT)
		draw_mandelbrot(fractal);
	mlx_image_to_window(fractal->mlx_window, fractal->mlx_image, 0, 0);
	mlx_cursor_hook(fractal->mlx_window, mouse_callback, fractal);
	mlx_scroll_hook(fractal->mlx_window, scroll_callback, fractal);
	mlx_key_hook(fractal->mlx_window, key_callback, fractal);
	mlx_loop_hook(fractal->mlx_window, re_draw_fractal, fractal);
	mlx_loop(fractal->mlx_window);
	mlx_delete_image(fractal->mlx_window, fractal->mlx_image);
	mlx_terminate(fractal->mlx_window);
}
