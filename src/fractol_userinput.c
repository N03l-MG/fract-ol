/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_userinput.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kixik   <github.com/kixikCodes>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:18:42 by kixik             #+#    #+#             */
/*   Updated: 2024/11/22 18:34:04 by kixik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Handle mouse movement and dragging R and I sliders
void	mouse_callback(double xpos, double ypos, void *param)
{
	t_fractal	*fractal;
	int			width;

	fractal = (t_fractal *)param;
	width = WIDTH - 40;
	if (mlx_is_mouse_down(fractal->mlx_window, MLX_MOUSE_BUTTON_LEFT))
		slide(fractal, width, xpos, ypos);
}

// Handle mouse scrolling for zooming in and out
void	scroll_callback(double xoffset, double yoffset, void *param)
{
	t_fractal		*fractal;
	t_fractalscale	s;
	int				mouse_x;
	int				mouse_y;

	fractal = (t_fractal *)param;
	(void)xoffset;
	mlx_get_mouse_pos(fractal->mlx_window, &mouse_x, &mouse_y);
	s.aspect_ratio = (double)HEIGHT / WIDTH;
	s.re_range = fractal->max_re - fractal->min_re;
	s.im_range = s.re_range * s.aspect_ratio;
	s.cursor_re = fractal->min_re + (mouse_x / (double)WIDTH) * s.re_range;
	s.cursor_im = fractal->min_im + (mouse_y / (double)HEIGHT) * s.im_range;
	if (yoffset > 0)
	{
		s.re_range *= fractal->zoom_factor;
		s.im_range = s.re_range * s.aspect_ratio;
	}
	else if (yoffset < 0)
	{
		s.re_range /= fractal->zoom_factor;
		s.im_range = s.re_range * s.aspect_ratio;
	}
	rescale_view(fractal, &s);
	fractal->should_re_draw = true;
}

// Handle arrow key presses for movement
void	key_callback(mlx_key_data_t keydata, void *param)
{
	t_fractal	*fractal;
	double		move_factor;

	fractal = (t_fractal *)param;
	move_factor = 0.01;
	if (keydata.key == MLX_KEY_LEFT)
		move_view(fractal, -move_factor, 0);
	else if (keydata.key == MLX_KEY_RIGHT)
		move_view(fractal, move_factor, 0);
	else if (keydata.key == MLX_KEY_UP)
		move_view(fractal, 0, -move_factor);
	else if (keydata.key == MLX_KEY_DOWN)
		move_view(fractal, 0, move_factor);
	else if (keydata.key == MLX_KEY_ESCAPE)
		clean_stop(fractal);
}
