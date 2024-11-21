/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:27:47 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/20 18:42:09 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fractol_start(t_fractal_name name, char **args);

int	main(int argc, char *argv[])
{
	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		fractol_start(MANDELBROT, NULL);
	else if (argc == 4 && !ft_strncmp(argv[1], "julia", 5))
		fractol_start(JULIA, argv);
	else
	{
		ft_fprintf(2, "Invalid input arguments!\n");
		ft_fprintf(1, "Usage: [Fratal] If Julia: [R Comp] [I Comp]\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void fractol_start(t_fractal_name name, char **args)
{
	t_fractal *fractal;

	fractal = (t_fractal *)malloc(sizeof(t_fractal));
	if (!fractal)
		error_handler(ERR_MEMORY, NULL);
	ft_memset(fractal, 0, sizeof(t_fractal));
	fractal->min_re = -2.0;
	fractal->max_re = 2.0;
	fractal->min_im = -2.0;
	fractal->max_im = 2.0;
	fractal->zoom_factor = 0.9;
	fractal->should_re_draw = false;
	if (name == JULIA)
	{
		if (!args || !args[1] || !args[2])
			error_handler(ERR_INVALID, fractal);
		fractal->c_re = atof(args[1]); // TODO: make own ft_atof
		fractal->c_im = atof(args[2]);
		fractal->slider_re = (fractal->c_re + 2.0) / 4.0;
		fractal->slider_im = (fractal->c_im + 2.0) / 4.0;
	}
	render_fractal(name, fractal);
	free(fractal);
}
