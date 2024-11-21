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

static int	get_color(int iterations) // TODO: make norminette compliant
{
	if (iterations == MAX_ITER)
		return (0x000000);
	int r = (iterations * 10) % 256;
	int g = (iterations * 1) % 256;
	int b = (iterations * 3) % 256;

	return (r << 16) | (g << 8) | b;
}

void	re_draw_fractal(void *f) // TODO: Adapt for other hooks and mandelbrot
{
	t_fractal	*fractal = (t_fractal *)f;

	if (fractal->should_re_draw) {
		draw_julia(fractal);
		draw_sliders(fractal);
		mlx_image_to_window(fractal->mlx_window, fractal->mlx_image, 0, 0);
		fractal->should_re_draw = false;
	}
}

void	draw_julia(t_fractal *fractal) // TODO: refacting hell
{
	int				x, y, iter;
	double			z_re, z_im, z_re2, z_im2;
	unsigned char	*pixel;
	double			aspect_ratio = (double)HEIGHT / WIDTH;
	double			re_range = fractal->max_re - fractal->min_re;
	double			im_range = re_range * aspect_ratio;

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			z_re = fractal->min_re + (x / (double)WIDTH) * re_range;
			z_im = fractal->min_im + (y / (double)HEIGHT) * im_range;

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
			pixel[0] = (color >> 16) & 0xFF; // Red
			pixel[1] = (color >> 8) & 0xFF;  // Green
			pixel[2] = color & 0xFF;         // Blue
			pixel[3] = 0xFF;                 // Alpha
		}
	}
}

void	draw_mandelbrot(t_fractal *fractal) // TODO: refacting hell
{
	int				x, y, iter;
	double			z_re, z_im, c_re, c_im, z_re2, z_im2;
	unsigned char	*pixel;
	double			re_range = fractal->max_re - fractal->min_re;
	double			im_range = fractal->max_im - fractal->min_im;

	for (y = 0; y < HEIGHT; y++)
	{
		for (x = 0; x < WIDTH; x++)
		{
			c_re = fractal->min_re + (x / (double)WIDTH) * re_range;
			c_im = fractal->min_im + (y / (double)HEIGHT) * im_range;
			z_re = 0.0;
			z_im = 0.0;
			iter = 0;
			while (iter < MAX_ITER && (z_re * z_re + z_im * z_im) <= 4)
			{
				z_re2 = z_re * z_re - z_im * z_im + c_re;
				z_im2 = 2 * z_re * z_im + c_im;
				z_re = z_re2;
				z_im = z_im2;
				iter++;
			}
			int color = get_color(iter);
			int pixel_index = (y * WIDTH + x) * 4;
			pixel = &fractal->image_data[pixel_index];
			pixel[0] = (color >> 16) & 0xFF; // Red
			pixel[1] = (color >> 8) & 0xFF;  // Green
			pixel[2] = color & 0xFF;         // Blue
			pixel[3] = 0xFF;                 // Alpha
		}
	}
}

void	render_fractal(t_fractal_name name, t_fractal *fractal) // TODO: Better handling of chosen fractal
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
	if (name == JULIA)
	{
		draw_julia(fractal);
		draw_sliders(fractal);
	}
	else if (name == MANDELBROT)
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
