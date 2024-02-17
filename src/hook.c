/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:24:32 by wel-safa          #+#    #+#             */
/*   Updated: 2024/02/17 20:52:23 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	recalc(t_img *img)
{
	if (img->type == MANDEL)
		calc_mandel(img);
	if (img->type == JULIA)
		calc_julia(img);
}

/*
hooked to event "key press" through mlx_key_hook
int key is the key code pressed
*/
int	keyhook(int key, t_img *img)
{
	if (key == ESC)
		exit_win(img);
	if (key == UP)
		img->sy0 -= 10 / img->zoom;
	if (key == DOWN)
		img->sy0 += 10 / img->zoom;
	if (key == RIGHT)
		img->sx0 += 10 / img->zoom;
	if (key == LEFT)
		img->sx0 -= 10 / img->zoom;
	if (key == SPACE)
		img->color = B_COLOR;
	if (key == SHIFT)
	{
		if (img->type == JULIA)
			init_julia(img);
		else
			init_mandel(img);
	}
	recalc(img);
	return (0);
}

/*
hooked to event "mouse click or scroll" through mlx_mouse_hook
int code is the code of mouse action
*/
int	mousehook(int code, int x, int y, t_img *img)
{
	if (code == 4 || code == 1)
		zoomin(x, y, img);
	if (code == 5 || code == 3)
		zoomout(x, y, img);
	if (code == 2)
		img->color = B_COLOR * code / y * x;
	recalc(img);
	return (0);
}
