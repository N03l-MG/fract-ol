/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:27:47 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/19 13:10:18 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int argc, char *argv[])
{
	if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		fractol_start(MANDELBROT);
	else if (argc == 4 && !ft_strncmp(argv[1], "julia", 5))
		fractol_start(JULIA);
	else
	{
		ft_printf("Invalid input arguments!\n");
		ft_printf("Usage: [Fratal] If Julia: [R Component] [I Component]\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	fractol_start(t_fractal_name name)
{
	t_fractal	fractal;

	if (name == MANDELBROT)
	{
		ft_printf("Log: rendering Mandelbrot set.\n");
		render_fractal(name, &fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else if (name == JULIA)
	{
		ft_printf("Log: rendering Julia set.\n");
		render_fractal(name, &fractal);
		mlx_loop(fractal.mlx_connection);
	}
}
