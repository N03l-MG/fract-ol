/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_userinput.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:18:42 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/22 18:34:04 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	slide(t_fractal *fractal, int width, double xpos, double ypos)
{
	if (ypos > HEIGHT - 60 && ypos < HEIGHT - 50)
	{
		fractal->slider_active = 1;
		fractal->slider_re = (xpos - 20) / width;
		fractal->slider_re = fmax(0, fmin(1, fractal->slider_re));
		fractal->c_re = -2.0 + fractal->slider_re * 4.0;
		fractal->should_re_draw = true;
	}
	else if (ypos > HEIGHT - 40 && ypos < HEIGHT - 30)
	{
		fractal->slider_active = 2;
		fractal->slider_im = (xpos - 20) / width;
		fractal->slider_im = fmax(0, fmin(1, fractal->slider_im));
		fractal->c_im = -2.0 + fractal->slider_im * 4.0;
		fractal->should_re_draw = true;
	}
	else
		fractal->slider_active = 0;
}

static void	rescale_view(t_fractal *fractal, t_fractalscale *s)
{
	fractal->min_re = s->cursor_re - (s->cursor_re - fractal->min_re)
		* (s->re_range / (fractal->max_re - fractal->min_re));
	fractal->max_re = s->cursor_re + (fractal->max_re - s->cursor_re)
		* (s->re_range / (fractal->max_re - fractal->min_re));
	fractal->min_im = s->cursor_im - (s->cursor_im - fractal->min_im)
		* (s->im_range / (fractal->max_im - fractal->min_im));
	fractal->max_im = s->cursor_im + (fractal->max_im - s->cursor_im)
		* (s->im_range / (fractal->max_im - fractal->min_im));
}

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
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_stop(fractal);
}
