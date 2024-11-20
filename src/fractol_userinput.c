/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_userinput.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:18:42 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/20 18:28:10 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mouse_callback(double xpos, double ypos, void *param)
{
	t_fractal *fractal = (t_fractal *)param;
	int slider_width = WIDTH - 40;

	// Get the current time in seconds
	double current_time = mlx_get_time();

	// Minimum time interval for updates (e.g., 50ms = 0.05 seconds)
	const double MIN_UPDATE_INTERVAL = 0.5;

	if (fractal->mouse_down)
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

		// Only update if enough time has passed
		if ((current_time - fractal->last_update_time) >= MIN_UPDATE_INTERVAL)
		{
			draw_julia(fractal);
			draw_sliders(fractal);
			mlx_image_to_window(fractal->mlx_window, fractal->mlx_image, 0, 0);

			// Update the last update time
			fractal->last_update_time = current_time;
		}
	}
}

void	click_callback(mouse_key_t bt, action_t act, modifier_key_t m, void *f)
{
	t_fractal	*fractal;

	(void)m;
	fractal = (t_fractal *)f;
	if (bt == MLX_MOUSE_BUTTON_LEFT)
	{
		if (act == MLX_PRESS)
			fractal->mouse_down = 1;
		else if (act == MLX_RELEASE)
			fractal->mouse_down = 0;
	}
}
