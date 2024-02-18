/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wix.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:17:31 by wel-safa          #+#    #+#             */
/*   Updated: 2024/02/18 20:47:39 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
Puts pixel on image at coordinates (x, y)
If bits per pixel is not 32, we call mlx_get_color_value to translate color
to fit the bits per pixel requirement of the image.
The bits position depends on the computer's endian,
bits are assigned accordingly.
*/
int	put_pixel_to_img(t_img *img, int x, int y, int color)
{
	int	pixel;

	if (img->pixel_bits != 32)
	{
		color = mlx_get_color_value(img->mlx, color);
	}
	pixel = (y * img->line_bytes) + (x * 4);
	if (img->endian == 1)
	{
		img->addr[pixel + 0] = (color >> 24);
		img->addr[pixel + 1] = (color >> 16) & 0xFF;
		img->addr[pixel + 2] = (color >> 8) & 0xFF;
		img->addr[pixel + 3] = (color) & 0xFF;
	}
	else if (img->endian == 0)
	{
		img->addr[pixel + 0] = (color) & 0xFF;
		img->addr[pixel + 1] = (color >> 8) & 0xFF;
		img->addr[pixel + 2] = (color >> 16) & 0xFF;
		img->addr[pixel + 3] = (color >> 24);
	}
	return (0);
}

void	zero_img(t_img *img)
{
	img->px = -1;
	img->py = -1;
	while (++img->px < WIN_WIDTH)
	{
		img->py = -1;
		while (++img->py < WIN_HEIGHT)
			put_pixel_to_img(img, img->px, img->py, 0);
	}
}

int	exit_win(t_img *img)
{
	mlx_destroy_image(img->mlx, img->img_ptr);
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_display(img->mlx);
	free(img->mlx);
	exit (1);
}

/*
creates int representation of color RGB and Transparency T
int input ranges = 0 -> 255
TRGB Representation of colors
0xTTRRGGBB
red		0x00FF0000
green	0x0000FF00
blue	0x000000FF
*/
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
