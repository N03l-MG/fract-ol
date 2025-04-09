/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_colour.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kixik   <github.com/kixikCodes>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 16:09:38 by kixik             #+#    #+#             */
/*   Updated: 2024/11/22 16:59:23 by kixik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	get_color(int iterations)
{
	int		r;
	int		g;
	int		b;
	double	t;
	double	phase;

	if (iterations == MAX_ITER)
		return (0x000000);
	t = (double)iterations / MAX_ITER * M_PI * 2;
	phase = 3.5;
	r = (int)(127.5 * (1 + sin(t + phase))) % 256;
	g = (int)(100 * (1 + sin(t + phase + M_PI / 2))) % 256;
	b = (int)(90 * (1 + sin(t + phase + M_PI))) % 256;
	return ((r << 16) | (g << 8) | b);
}

void	assign_pixel_color(int x, int y, int iter, t_fractal *fractal)
{
	unsigned char	*pixel;
	int				color;
	int				pixel_index;

	color = get_color(iter);
	pixel_index = (y * WIDTH + x) * 4;
	pixel = &fractal->image_data[pixel_index];
	pixel[0] = (color >> 16) & 0xFF;
	pixel[1] = (color >> 8) & 0xFF;
	pixel[2] = color & 0xFF;
	pixel[3] = 0xFF;
}
