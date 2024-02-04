/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:47:30 by wel-safa          #+#    #+#             */
/*   Updated: 2024/02/04 20:24:38 by wel-safa         ###   ########.fr       */
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

# define TITLE		"fract-ol"
# define WIN_SIZE	600.0
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
	double	it;
	double	it_max;
	double	x;
	double	y;
	double	sx;
	double	sy;
	double	xtemp;
	int		color;
}				t_img;

#endif