/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_ui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:18:44 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/20 18:30:30 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Julia set sliders for R and I components of current complex number
void	draw_sliders(t_fractal *fractal) // TODO: make norminette compliant
{
	int	x, y;
	int	slider_width = WIDTH - 40;

	for (y = HEIGHT - 60; y < HEIGHT - 50; y++)
	{
		for (x = 20; x < 20 + slider_width; x++)
		{
			int color = (x < 20 + (fractal->slider_re * slider_width)) ? 0xFF0000 : 0xAAAAAA;
			int pixel_index = (y * WIDTH + x) * 4;
			fractal->mlx_image->pixels[pixel_index + 0] = (color >> 16) & 0xFF; // Red
			fractal->mlx_image->pixels[pixel_index + 1] = (color >> 8) & 0xFF;  // Green
			fractal->mlx_image->pixels[pixel_index + 2] = color & 0xFF;         // Blue
			fractal->mlx_image->pixels[pixel_index + 3] = 0xFF;                // Alpha
		}
	}
	for (y = HEIGHT - 40; y < HEIGHT - 30; y++)
	{
		for (x = 20; x < 20 + slider_width; x++)
		{
			int color = (x < 20 + (fractal->slider_im * slider_width)) ? 0x00FF00 : 0xAAAAAA;
			int pixel_index = (y * WIDTH + x) * 4;
			fractal->mlx_image->pixels[pixel_index + 0] = (color >> 16) & 0xFF; // Red
			fractal->mlx_image->pixels[pixel_index + 1] = (color >> 8) & 0xFF;  // Green
			fractal->mlx_image->pixels[pixel_index + 2] = color & 0xFF;         // Blue
			fractal->mlx_image->pixels[pixel_index + 3] = 0xFF;                // Alpha
		}
	}
}

// More UI will be implemented!
