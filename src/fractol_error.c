/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kixik   <github.com/kixikCodes>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:50:17 by kixik             #+#    #+#             */
/*   Updated: 2024/11/22 18:32:07 by kixik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	error_handler(t_error error, t_fractal *fractal)
{
	if (error == ERR_MEMORY)
		ft_fprintf(2, "Error: Failed to allocate memory.\n");
	else if (error == ERR_INVALID)
		ft_fprintf(2, "Error: Invalid parameters for fractal.\n");
	else if (error == ERR_WINDOW)
		ft_fprintf(2, "Error: Failed to initialize MLX window.\n");
	else if (error == ERR_IMAGE)
	{
		ft_fprintf(2, "Error: Failed to create MLX image.\n");
		mlx_terminate(fractal->mlx_window);
	}
	else if (error == ERR_DATA)
	{
		ft_fprintf(2, "Error: Failed to access image pixel data.\n");
		mlx_delete_image(fractal->mlx_window, fractal->mlx_image);
		mlx_terminate(fractal->mlx_window);
	}
	exit(EXIT_FAILURE);
}

void	clean_stop(t_fractal *fractal)
{
	if (fractal->mlx_image)
		mlx_delete_image(fractal->mlx_window, fractal->mlx_image);
	if (fractal->mlx_window)
		mlx_terminate(fractal->mlx_window);
	exit(EXIT_SUCCESS);
}
