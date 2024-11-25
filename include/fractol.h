/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmonzon <nmonzon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:39:00 by nmonzon           #+#    #+#             */
/*   Updated: 2024/11/22 18:02:47 by nmonzon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/include/libft.h"
# include "../MLX42/MLX42.h"
# include <math.h>

# define MAX_ITER 200
# define WIDTH 1920
# define HEIGHT 1080

// Fractal types
typedef enum e_name
{
	MANDELBROT,
	JULIA,
	BURNING_SHIP
}	t_name;

// Errors types
typedef enum e_error
{
	ERR_MEMORY,
	ERR_INVALID,
	ERR_WINDOW,
	ERR_IMAGE,
	ERR_DATA
}	t_error;

// Fractal data structures
typedef struct s_fractal
{
	t_name			name;
	mlx_t			*mlx_window;
	mlx_image_t		*mlx_image;
	unsigned char	*image_data;
	float			c_re;
	float			c_im;
	float			min_re;
	float			max_re;
	float			min_im;
	float			max_im;
	float			zoom_factor;
	float			slider_re;
	float			slider_im;
	int				slider_active;
	bool			should_re_draw;
	double			last_update_time;
}	t_fractal;

typedef struct s_juliaset
{
	float	z_re;
	float	z_im;
	float	z_re2;
	float	z_im2;
	float	aspect_ratio;
	float	re_range;
	float	im_range;
}	t_juliaset;

typedef struct s_mandelbrotset
{
	float	z_re;
	float	z_im;
	float	c_re;
	float	c_im;
	float	z_re2;
	float	z_im2;
	float	aspect_ratio;
	float	re_range;
	float	im_range;
}	t_mandelbrotset;

typedef struct s_fractalscale
{
	double	aspect_ratio;
	double	cursor_re;
	double	cursor_im;
	double	re_range;
	double	im_range;
}	t_fractalscale;

// Error handing
void	error_handler(t_error error, t_fractal *fractal);
void	clean_stop(t_fractal *fractal);

// Rendering
void	render_fractal(t_fractal *fractal);
void	draw_julia(t_fractal *fractal);
void	draw_mandelbrot(t_fractal *fractal);
void	assign_pixel_color(int x, int y, int iter, t_fractal *fractal);
void	draw_sliders(t_fractal *fractal);

// User input hooks
void	mouse_callback(double xpos, double ypos, void *param);
void	scroll_callback(double xoffset, double yoffset, void *param);
void	key_callback(mlx_key_data_t keydata, void *param);

// Util functions
float	ft_atof(char *s);
void	slide(t_fractal *fractal, int width, double xpos, double ypos);
void	rescale_view(t_fractal *fractal, t_fractalscale *s);
void	move_view(t_fractal *fractal, double re_offset, double im_offset);

#endif
