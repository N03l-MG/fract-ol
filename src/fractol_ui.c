/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_ui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:18:44 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/21 17:47:44 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_slider_re(t_fractal *fractal);
static void	draw_slider_im(t_fractal *fractal);

// Julia set sliders for R and I components of current complex number
void	draw_sliders(t_fractal *fractal)
{
	draw_slider_re(fractal);
	draw_slider_im(fractal);
}

static void	draw_slider_re(t_fractal *fractal)
{
	int	x;
	int	y;
	int	slider_width;
	int	color;
	int	pixel_index;

	x = 20;
	y = HEIGHT - 60;
	slider_width = WIDTH - 40;
	while (y < HEIGHT - 50)
	{
		x = 0;
		while (x < 20 + slider_width)
		{
			color = (x < 20 + (fractal->slider_re * slider_width)) ? 0xFF0000 : 0xAAAAAA;
			pixel_index = (y * WIDTH + x) * 4;
			fractal->mlx_image->pixels[pixel_index + 0] = (color >> 16) & 0xFF;
			fractal->mlx_image->pixels[pixel_index + 1] = (color >> 8) & 0xFF;
			fractal->mlx_image->pixels[pixel_index + 2] = color & 0xFF;
			fractal->mlx_image->pixels[pixel_index + 3] = 0xFF;
			x++;
		}
		y++;
	}
}

static void	draw_slider_im(t_fractal *fractal)
{
	int	x;
	int	y;
	int	slider_width;
	int	color;
	int	pixel_index;

	x = 20;
	y = HEIGHT - 40;
	slider_width = WIDTH - 40;
	while (y < HEIGHT - 30)
	{
		x = 0;
		while (x < 20 + slider_width)
		{
			color = (x < 20 + (fractal->slider_im * slider_width)) ? 0x00FF00 : 0xAAAAAA;
			pixel_index = (y * WIDTH + x) * 4;
			fractal->mlx_image->pixels[pixel_index + 0] = (color >> 16) & 0xFF;
			fractal->mlx_image->pixels[pixel_index + 1] = (color >> 8) & 0xFF;
			fractal->mlx_image->pixels[pixel_index + 2] = color & 0xFF;
			fractal->mlx_image->pixels[pixel_index + 3] = 0xFF;
			x++;
		}
		y++;
	}
}

// More UI will be implemented!
