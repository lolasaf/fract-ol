/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:47:30 by wel-safa          #+#    #+#             */
/*   Updated: 2024/02/18 16:40:05 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"

/*include more h files here from inc dir*/

# define TITLE "fract-ol"
# define MANDEL 1
# define JULIA 2 
# define WIN_WIDTH 1000
# define WIN_HEIGHT 800
# define SPACE 32
# define SHIFT 65506
# define ESC 65307
# define UP 65362
# define DOWN 65364
# define RIGHT 65363
# define LEFT 65361
# define B_COLOR 0xFCBE11

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct s_img
{
	int		type;
	void	*mlx;
	void	*win;
	void	*img_ptr;
	char	*addr;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	double	zoom;
	double	sx0;
	double	sy0;
	double	px;
	double	py;
	int		it;
	int		it_max;
	double	x;
	double	y;
	double	sx;
	double	sy;
	double	a;
	double	b;
	double	xtemp;
	int		color;
}				t_img;

int		put_pixel_to_img(t_img *img, int x, int y, int color);
void	zero_img(t_img *img);
int		exit_win(t_img *img);
int		create_trgb(int t, int r, int g, int b);

int		keyhook(int key, t_img *data);
int		mousehook(int code, int x, int y, t_img *img);

void	mandelbrot(t_img *img);
void	init_mandel(t_img *img);
void	calc_mandel(t_img *img);

int		zoomin(int x, int y, t_img *img);
int		zoomout(int x, int y, t_img *img);

void	filledjulia(t_img *img);
void	init_julia(t_img *img);
void	calc_julia(t_img *img);

#endif