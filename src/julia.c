/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:40:36 by wel-safa          #+#    #+#             */
/*   Updated: 2024/02/18 16:34:08 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	filledjulia(t_img *img)
{
	init_julia(img);
	calc_julia(img);
}

void	init_julia(t_img *img)
{
	img->type = JULIA;
	img->zoom = 230;
	img->sx0 = -2.05;
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
	img->color = B_COLOR;
}

void	calc_julia_it(t_img *img)
{
	img->xtemp = img->x * img->x - img->y * img->y + img->a;
	img->y = 2 * img->x * img->y + img->b;
	img->x = img->xtemp;
	img->it++;
}

/*
for polznomial f(z) = z^2 + c;
fix complex number c as input;
each pixel on screen is a complex number z;
iterate starting at z over the function
c = a + b * i*/
void	calc_julia(t_img *img)
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
			img->x = img->sx;
			img->y = img->sy;
			while (img->x * img->x + img->y * img->y <= 4 
				&& img->it < img->it_max)
			{
				calc_julia_it(img);
			}
			if (img->it == img->it_max)
				put_pixel_to_img(img, img->px, img->py, 0x000000);
			else
				put_pixel_to_img(img, img->px, img->py, img->color * img->it);
		}
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img_ptr, 0, 0);
}
