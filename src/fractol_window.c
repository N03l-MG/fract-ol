/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:40:31 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/20 18:21:52 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_color(int iterations)
{
	if (iterations == MAX_ITER)
		return (0x000000);
	int r = (iterations * 1) % 256;
	int g = (iterations * 5) % 256;
	int b = (iterations * 3) % 256;

	return (r << 16) | (g << 8) | b;
}

void	draw_julia(t_fractal *fractal)
{
	int x, y, iter;
	float z_re, z_im, z_re2, z_im2;
	float scale = 4.0 / WIDTH;
	unsigned char *pixel;

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			z_re = (x - WIDTH / 2) * scale;
			z_im = (y - HEIGHT / 2) * scale;
			iter = 0;
			while (iter < MAX_ITER && (z_re * z_re + z_im * z_im) <= 4)
			{
				z_re2 = z_re * z_re - z_im * z_im + fractal->c_re;
				z_im2 = 2 * z_re * z_im + fractal->c_im;
				z_re = z_re2;
				z_im = z_im2;
				iter++;
			}
			int color = get_color(iter);
			int pixel_index = (y * WIDTH + x) * 4;
			pixel = &fractal->image_data[pixel_index];
			pixel[0] = (color >> 16) & 0xFF;  // Red
			pixel[1] = (color >> 8) & 0xFF;   // Green
			pixel[2] = color & 0xFF;          // Blue
			pixel[3] = 0xFF;                  // Alpha
		}
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
	draw_julia(fractal);
	draw_sliders(fractal);
	mlx_image_to_window(fractal->mlx_window, fractal->mlx_image, 0, 0);
	mlx_cursor_hook(fractal->mlx_window, mouse_callback, fractal);
	mlx_mouse_hook(fractal->mlx_window, click_callback, fractal);
	mlx_loop(fractal->mlx_window);
	mlx_delete_image(fractal->mlx_window, fractal->mlx_image);
	mlx_terminate(fractal->mlx_window);
}
