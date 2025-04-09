/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kixik   <github.com/kixikCodes>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:27:47 by kixik             #+#    #+#             */
/*   Updated: 2024/11/22 18:32:14 by kixik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fractol_start(t_name name, char **args);

int	main(int argc, char *argv[])
{
	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		fractol_start(MANDELBROT, NULL);
	else if (argc == 2 && !ft_strncmp(argv[1], "burningship", 11))
		fractol_start(BURNING_SHIP, NULL);
	else if (argc == 4 && !ft_strncmp(argv[1], "julia", 5))
		fractol_start(JULIA, argv);
	else
	{
		ft_fprintf(2, "Invalid input arguments!\n");
		ft_fprintf(1, "Usage: ./fractol [Name]\n");
		ft_fprintf(1, "If Julia: ./fractol [Name] [Real c] [Imaginary c]\n");
		return (EXIT_FAILURE);
	}
}

static void	fractol_start(t_name name, char **args)
{
	t_fractal	fractal;

	ft_memset(&fractal, 0, sizeof(t_fractal));
	fractal.name = name;
	fractal.min_re = -2.0;
	fractal.max_re = 2.0;
	fractal.min_im = -2.0;
	fractal.max_im = 2.0;
	fractal.zoom_factor = 0.9;
	fractal.should_re_draw = false;
	if (name == JULIA)
	{
		if (!args || !args[1] || !args[2])
			error_handler(ERR_INVALID, &fractal);
		fractal.c_re = ft_atof(args[1]);
		fractal.c_im = ft_atof(args[2]);
		fractal.slider_re = (fractal.c_re + 2.0) / 4.0;
		fractal.slider_im = (fractal.c_im + 2.0) / 4.0;
	}
	render_fractal(&fractal);
}
