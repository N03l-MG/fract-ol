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

	double current_time = mlx_get_time();
	const double MIN_UPDATE_INTERVAL = 1 / 60.0;

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

		// Only update if enough time has passed
		if ((current_time - fractal->last_update_time) >= MIN_UPDATE_INTERVAL)
		{
			fractal->should_re_draw = 1;
			// Update the last update time
			fractal->last_update_time = current_time;
		}
	}
}
