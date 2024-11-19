/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:50:17 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/19 15:06:16 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// void	free_all(t_fractal *fractal)
// {
// 	// free stuff with a loop
// }

void	error_handler(t_error error) // , t_fractal *fractal
{
	if (error == ERR_MEMORY)
		ft_fprintf(2, "Error: failed to allocate memory.\n");
	if (error == ERR_INVALID)
		ft_fprintf(2, "Error: invalid parameters for fractal.\n");
	//free_all(fractal);
	exit(EXIT_FAILURE);
}
