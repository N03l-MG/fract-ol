/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_ui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kixik   <github.com/kixikCodes>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:18:44 by kixik             #+#    #+#             */
/*   Updated: 2024/11/22 17:34:47 by kixik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	draw_slider_re(t_fractal *fractal);
static void	draw_slider_im(t_fractal *fractal);
static void	color_slider(t_fractal *fractal, int width, int x, int y);

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
	int	width;

	y = HEIGHT - 60;
	width = WIDTH - 40;
	while (y < HEIGHT - 50)
	{
		x = 20;
		while (x < width)
		{
			color_slider(fractal, x, y, fractal->slider_re * width);
			x++;
		}
		y++;
	}
}

static void	draw_slider_im(t_fractal *fractal)
{
	int	x;
	int	y;
	int	width;

	y = HEIGHT - 40;
	width = WIDTH - 40;
	while (y < HEIGHT - 30)
	{
		x = 20;
		while (x < width)
		{
			color_slider(fractal, x, y, fractal->slider_im * width);
			x++;
		}
		y++;
	}
}

static void	color_slider(t_fractal *fractal, int x, int y, int width)
{
	int	color;
	int	pixel_index;

	if (x < width)
		color = 0xFFFFFF;
	else
		color = 0xAAAAAA;
	pixel_index = (y * WIDTH + x) * 4;
	fractal->mlx_image->pixels[pixel_index + 0] = (color >> 16) & 0xFF;
	fractal->mlx_image->pixels[pixel_index + 1] = (color >> 8) & 0xFF;
	fractal->mlx_image->pixels[pixel_index + 2] = color & 0xFF;
	fractal->mlx_image->pixels[pixel_index + 3] = 0xFF;
}
