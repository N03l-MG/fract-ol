/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:39:00 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/20 18:22:18 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "../MLX42/MLX42.h"
# include <math.h>

# define MAX_ITER 200
# define WIDTH 1920
# define HEIGHT 1080

typedef enum e_fractal_name
{
	MANDELBROT,
	JULIA
	// etc
}	t_fractal_name;

typedef enum e_error
{
	ERR_MEMORY,
	ERR_INVALID,
	ERR_WINDOW,
	ERR_IMAGE,
	ERR_DATA,
}	t_error;

typedef struct s_fractal
{
	mlx_t			*mlx_window;
	mlx_image_t		*mlx_image;
	unsigned char	*image_data;
	float			c_re;
	float			c_im;
	float			slider_re;
	float			slider_im;
	int				slider_active;
	int				should_re_draw;
	double			last_update_time;
}	t_fractal;

void	error_handler(t_error error, t_fractal *fractal);
void	render_fractal(t_fractal *fractal);
void	draw_julia(t_fractal *fractal);
void	draw_sliders(t_fractal *fractal);
void	mouse_callback(double xpos, double ypos, void *param);

#endif