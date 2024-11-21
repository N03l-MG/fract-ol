/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:37:17 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/21 17:58:07 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	draw_julia(t_fractal *fractal)
{
	int				x;
	int				y;
	int				iter;
	double			z_re;
	double			z_im;
	double			z_re2;
	double			z_im2;
	unsigned char	*pixel;
	double			aspect_ratio;
	double			re_range;
	double			im_range;
	int				color;
	int				pixel_index;

	aspect_ratio = (double)HEIGHT / WIDTH;
	re_range = fractal->max_re - fractal->min_re;
	im_range = re_range * aspect_ratio;
	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
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
			color = get_color(iter);
			pixel_index = (y * WIDTH + x) * 4;
			pixel = &fractal->image_data[pixel_index];
			pixel[0] = (color >> 16) & 0xFF;
			pixel[1] = (color >> 8) & 0xFF;
			pixel[2] = color & 0xFF;
			pixel[3] = 0xFF;
			x++;
		}
		y++;
	}
}

void	draw_mandelbrot(t_fractal *fractal)
{
	int				x;
	int				y;
	int				iter;
	double			z_re;
	double			z_im;
	double			c_re;
	double			c_im;
	double			z_re2;
	double			z_im2;
	unsigned char	*pixel;
	double			aspect_ratio;
	double			re_range;
	double			im_range;
	int				color;
	int				pixel_index;

	aspect_ratio = (double)HEIGHT / WIDTH;
	re_range = fractal->max_re - fractal->min_re;
	im_range = re_range * aspect_ratio;
	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
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
			color = get_color(iter);
			pixel_index = (y * WIDTH + x) * 4;
			pixel = &fractal->image_data[pixel_index];
			pixel[0] = (color >> 16) & 0xFF;
			pixel[1] = (color >> 8) & 0xFF;
			pixel[2] = color & 0xFF;
			pixel[3] = 0xFF;
			x++;
		}
		y++;
	}
}
