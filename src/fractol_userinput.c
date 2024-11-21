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
	double			current_time = mlx_get_time();
	const double	MIN_UPDATE_INTERVAL = 1 / 60.0;

	if (mlx_is_mouse_down(fractal->mlx_window, MLX_MOUSE_BUTTON_LEFT))
	{
		if (ypos > HEIGHT - 60 && ypos < HEIGHT - 50)
		{
			fractal->slider_active = 1;
			fractal->slider_re = (xpos - 20) / slider_width;
			fractal->slider_re = fmax(0, fmin(1, fractal->slider_re));
			fractal->c_re = -2.0 + fractal->slider_re * 4.0;
		}
		else if (ypos > HEIGHT - 40 && ypos < HEIGHT - 30)
		{
			fractal->slider_active = 2;
			fractal->slider_im = (xpos - 20) / slider_width;
			fractal->slider_im = fmax(0, fmin(1, fractal->slider_im));
			fractal->c_im = -2.0 + fractal->slider_im * 4.0;
		}
		else
			fractal->slider_active = 0;
		if ((current_time - fractal->last_update_time) >= MIN_UPDATE_INTERVAL)
		{
			fractal->should_re_draw = true;
			fractal->last_update_time = current_time;
		}
	}
}

// Handle mouse scrolling for zooming in and out
void	scroll_callback(double xoffset, double yoffset, void *param) // TODO: refactoring hell
{
	t_fractal	*fractal = (t_fractal *)param;
	double		cursor_re, cursor_im, re_range, im_range;
	int			mouse_x, mouse_y;
	(void)xoffset;

	mlx_get_mouse_pos(fractal->mlx_window, &mouse_x, &mouse_y);
	double aspect_ratio = (double)HEIGHT / WIDTH;
	re_range = fractal->max_re - fractal->min_re;
	im_range = re_range * aspect_ratio;
	cursor_re = fractal->min_re + (mouse_x / (double)WIDTH) * re_range;
	cursor_im = fractal->min_im + (mouse_y / (double)HEIGHT) * im_range;
	if (yoffset > 0)
	{
		re_range *= fractal->zoom_factor;
		im_range = re_range * aspect_ratio;
	}
	else if (yoffset < 0)
	{
		re_range /= fractal->zoom_factor;
		im_range = re_range * aspect_ratio;
	}
	fractal->min_re = cursor_re - re_range / 2;
	fractal->max_re = cursor_re + re_range / 2;
	fractal->min_im = cursor_im - im_range / 2;
	fractal->max_im = cursor_im + im_range / 2;
	if (fractal->name == JULIA)
	{
		draw_julia(fractal);
		draw_sliders(fractal);
	}
	else
		draw_mandelbrot(fractal);
	mlx_image_to_window(fractal->mlx_window, fractal->mlx_image, 0, 0);
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
	}
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		fractal->min_re += move_factor;
		fractal->max_re += move_factor;
	}
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		fractal->min_im -= move_factor;
		fractal->max_im -= move_factor;
	}
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		fractal->min_im += move_factor;
		fractal->max_im += move_factor;
	}
	if (fractal->name == JULIA)
	{
		draw_julia(fractal);
		draw_sliders(fractal);
	}
	else
		draw_mandelbrot(fractal);
	mlx_image_to_window(fractal->mlx_window, fractal->mlx_image, 0, 0);
}
