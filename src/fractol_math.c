/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kixik   <github.com/kixikCodes>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:37:17 by kixik             #+#    #+#             */
/*   Updated: 2024/11/22 17:10:50 by kixik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	complex_function_julia(t_fractal *fractal, t_juliaset *j)
{
	j->z_re2 = j->z_re * j->z_re - j->z_im * j->z_im + fractal->c_re;
	j->z_im2 = 2 * j->z_re * j->z_im + fractal->c_im;
	j->z_re = j->z_re2;
	j->z_im = j->z_im2;
}

static void	complex_function_mandels(t_fractal *fractal, t_mandelbrotset *m)
{
	if (fractal->name == MANDELBROT)
	{
		m->z_re2 = m->z_re * m->z_re - m->z_im * m->z_im + m->c_re;
		m->z_im2 = 2 * m->z_re * m->z_im + m->c_im;
		m->z_re = m->z_re2;
		m->z_im = m->z_im2;
	}
	else if (fractal->name == BURNING_SHIP)
	{
		m->z_re2 = m->z_re * m->z_re - m->z_im * m->z_im + m->c_re;
		m->z_im2 = 2 * fabsf(m->z_re * m->z_im) + m->c_im;
		m->z_re = m->z_re2;
		m->z_im = m->z_im2;
	}
}

void	draw_julia(t_fractal *fractal)
{
	int			x;
	int			y;
	int			iter;
	t_juliaset	j;

	j.aspect_ratio = (float)HEIGHT / WIDTH;
	j.re_range = fractal->max_re - fractal->min_re;
	j.im_range = j.re_range * j.aspect_ratio;
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			j.z_re = fractal->min_re + (x / (float)WIDTH) * j.re_range;
			j.z_im = fractal->min_im + (y / (float)HEIGHT) * j.im_range;
			iter = -1;
			while (++iter < MAX_ITER && (j.z_re * j.z_re + j.z_im * j.z_im) < 5)
				complex_function_julia(fractal, &j);
			assign_pixel_color(x, y, iter, fractal);
		}
	}
}

void	draw_mandelbrot(t_fractal *fractal)
{
	int				x;
	int				y;
	int				iter;
	t_mandelbrotset	m;

	m.aspect_ratio = (float)HEIGHT / WIDTH;
	m.re_range = fractal->max_re - fractal->min_re;
	m.im_range = m.re_range * m.aspect_ratio;
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			m.c_re = fractal->min_re + (x / (float)WIDTH) * m.re_range;
			m.c_im = fractal->min_im + (y / (float)HEIGHT) * m.im_range;
			m.z_re = 0.0;
			m.z_im = 0.0;
			iter = -1;
			while (++iter < MAX_ITER && (m.z_re * m.z_re + m.z_im * m.z_im) < 5)
				complex_function_mandels(fractal, &m);
			assign_pixel_color(x, y, iter, fractal);
		}
	}
}
