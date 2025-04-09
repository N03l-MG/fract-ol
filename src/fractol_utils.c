/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_colour.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kixik   <github.com/kixikCodes>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:57:05 by kixik             #+#    #+#             */
/*   Updated: 2024/11/22 22:59:23 by kixik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	count_decimals(char *str)
{
	int	count;

	count = 0;
	while (*str && *str != '.')
		str++;
	if (!*str)
		return (0);
	str++;
	while (*str && ft_isdigit(*str) == 1)
	{
		count++;
		str++;
	}
	return (count);
}

float	ft_atof(char *str)
{
	int	result;
	int	sign;
	int	i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
	{
		if (str[i] != '.')
			result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result / pow(10, count_decimals(str)));
}

void	slide(t_fractal *fractal, int width, double xpos, double ypos)
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

void	rescale_view(t_fractal *fractal, t_fractalscale *s)
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

void	move_view(t_fractal *fractal, double re_offset, double im_offset)
{
	fractal->min_re += re_offset;
	fractal->max_re += re_offset;
	fractal->min_im += im_offset;
	fractal->max_im += im_offset;
	fractal->should_re_draw = true;
}
