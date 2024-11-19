/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:40:31 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/19 15:14:18 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	render_fractal(t_fractal *fractal)
{
	fractal->mlx_window = mlx_init(250, 250, "fract-ol", true);
	if (!(fractal->mlx_window))
		error_handler(ERR_MEMORY);
	ft_fprintf(1, "Log: window started.\n");
}
