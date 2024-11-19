/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:39:00 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/19 15:14:35 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../MLX42/MLX42.h"

typedef enum e_fractal_name
{
	MANDELBROT,
	JULIA
	// etc
}	t_fractal_name;

typedef enum e_error
{
	ERR_MEMORY,
	ERR_INVALID
	// etc
}	t_error;

typedef struct s_fractal
{
	void		*mlx_window;
	mlx_image_t	*image;

}	t_fractal;

void	error_handler(t_error error);
void	render_fractal(t_fractal *fractal);

#endif