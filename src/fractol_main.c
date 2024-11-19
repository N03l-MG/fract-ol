/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:27:47 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/19 15:17:23 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	fractol_start(t_fractal_name name);

int	main(int argc, char *argv[])
{
	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		fractol_start(MANDELBROT);
	else if (argc == 4 && !ft_strncmp(argv[1], "julia", 5))
		fractol_start(JULIA);
	else
	{
		ft_fprintf(2, "Invalid input arguments!\n");
		ft_fprintf(1, "Usage: [Fratal] If Julia: [R Comp] [I Comp]\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	fractol_start(t_fractal_name name)
{
	t_fractal	fractal;

	if (name == MANDELBROT)
	{
		ft_fprintf(1, "Log: rendering Mandelbrot set.\n");
		render_fractal(&fractal);
		mlx_loop(fractal.mlx_window);
	}
	else if (name == JULIA)
	{
		ft_fprintf(1, "Log: rendering Julia set.\n");
		render_fractal(&fractal);
		mlx_loop(fractal.mlx_window);
	}
}
