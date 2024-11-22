/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_userinput.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:18:42 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/21 14:53:06 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Handle mouse movement and dragging R and I sliders
void	mouse_callback(double xpos, double ypos, void *param) // TODO: refactoring hell
{
	t_fractal		*fractal = (t_fractal *)param;
	int				slider_width = WIDTH - 40;

	if (mlx_is_mouse_down(fractal->mlx_window, MLX_MOUSE_BUTTON_LEFT))
	{
		if (ypos > HEIGHT - 60 && ypos < HEIGHT - 50)
		{
			fractal->slider_active = 1;
			fractal->slider_re = (xpos - 20) / slider_width;
			fractal->slider_re = fmax(0, fmin(1, fractal->slider_re));
			fractal->c_re = -2.0 + fractal->slider_re * 4.0;
			fractal->should_re_draw = true;
		}
		else if (ypos > HEIGHT - 40 && ypos < HEIGHT - 30)
		{
			fractal->slider_active = 2;
			fractal->slider_im = (xpos - 20) / slider_width;
			fractal->slider_im = fmax(0, fmin(1, fractal->slider_im));
			fractal->c_im = -2.0 + fractal->slider_im * 4.0;
			fractal->should_re_draw = true;
		}
		else
			fractal->slider_active = 0;
	}
}

// Handle mouse scrolling for zooming in and out
void scroll_callback(double xoffset, double yoffset, void *param) // TODO: refactoring hell
{
	t_fractal *fractal = (t_fractal *)param;
	double cursor_re, cursor_im, re_range, im_range;
	int mouse_x, mouse_y;

	(void)xoffset; // Unused parameter
	mlx_get_mouse_pos(fractal->mlx_window, &mouse_x, &mouse_y);

	double aspect_ratio = (double)HEIGHT / WIDTH;
	re_range = fractal->max_re - fractal->min_re;
	im_range = re_range * aspect_ratio;

	// Calculate the current fractal coordinates of the cursor
	cursor_re = fractal->min_re + (mouse_x / (double)WIDTH) * re_range;
	cursor_im = fractal->min_im + (mouse_y / (double)HEIGHT) * im_range;

	if (yoffset > 0) // Zoom in
	{
		re_range *= fractal->zoom_factor;
		im_range = re_range * aspect_ratio;
	}
	else if (yoffset < 0) // Zoom out
	{
		re_range /= fractal->zoom_factor;
		im_range = re_range * aspect_ratio;
	}

	// Adjust the boundaries to maintain the cursor position
	fractal->min_re = cursor_re - (cursor_re - fractal->min_re) * (re_range / (fractal->max_re - fractal->min_re));
	fractal->max_re = cursor_re + (fractal->max_re - cursor_re) * (re_range / (fractal->max_re - fractal->min_re));
	fractal->min_im = cursor_im - (cursor_im - fractal->min_im) * (im_range / (fractal->max_im - fractal->min_im));
	fractal->max_im = cursor_im + (fractal->max_im - cursor_im) * (im_range / (fractal->max_im - fractal->min_im));

	// Mark for redrawing
	fractal->should_re_draw = true;
}

// Handle arrow key presses for movement
void	key_callback(mlx_key_data_t keydata, void *param) // TODO: refactoring hell
{
	t_fractal	*fractal = (t_fractal *)param;
	double		move_factor = 0.1;

	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		fractal->min_re -= move_factor;
		fractal->max_re -= move_factor;
		fractal->should_re_draw = true;
	}
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		fractal->min_re += move_factor;
		fractal->max_re += move_factor;
		fractal->should_re_draw = true;
	}
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		fractal->min_im -= move_factor;
		fractal->max_im -= move_factor;
		fractal->should_re_draw = true;
	}
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		fractal->min_im += move_factor;
		fractal->max_im += move_factor;
		fractal->should_re_draw = true;
	}
}
