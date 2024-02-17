/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:14:34 by wel-safa          #+#    #+#             */
/*   Updated: 2024/02/17 20:56:25 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_img *img)
{
	init_mandel(img);
	calc_mandel(img);
}

void	init_mandel(t_img *img)
{
	img->type = MANDEL;
	img->zoom = 230;
	img->sx0 = -2.5;
	img->sy0 = -1.6;
	img->px = -1;
	img->py = -1;
	img->it = 0;
	img->it_max = 50;
	img->x = 0;
	img->y = 0;
	img->sx = 0;
	img->sy = 0;
	img->xtemp = 0;
	img->a = 0;
	img->b = 0;
	img->color = B_COLOR;
}

void	calc_mandel_it(t_img *img)
{
	img->xtemp = img->x * img->x - img->y * img->y + img->sx;
	img->y = 2 * img->x * img->y + img->sy;
	img->x = img->xtemp;
	img->it++;
}

void	calc_mandel(t_img *img)
{
	zero_img(img);
	img->px = -1;
	while (++img->px < WIN_WIDTH)
	{
		img->py = -1;
		while (++img->py < WIN_HEIGHT)
		{
			img->sx = img->sx0 + img->px / img->zoom;
			img->sy = img->sy0 + img->py / img->zoom;
			img->it = 0;
			img->x = 0;
			img->y = 0;
			while (img->x * img->x + img->y * img->y <= 4 
				&& img->it < img->it_max)
			{
				calc_mandel_it(img);
			}
			if (img->it == img->it_max)
				put_pixel_to_img(img, img->px, img->py, 0x000000);
			else
				put_pixel_to_img(img, img->px, img->py, img->color * img->it);
		}
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img_ptr, 0, 0);
}
