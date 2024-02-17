/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 16:30:33 by wel-safa          #+#    #+#             */
/*   Updated: 2024/02/17 16:30:46 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	zoomin(int x, int y, t_img *img)
{
	img->sx0 = (img->sx0 + x / img->zoom) - (x / (img->zoom * 1.1));
	img->sy0 = (img->sy0 + y / img->zoom) - (y / (img->zoom * 1.1));
	img->zoom *= 1.1;
	img->it_max++;
	return (1);
}

int	zoomout(int x, int y, t_img *img)
{
	img->sx0 = (img->sx0 + x / img->zoom) - x / (img->zoom / 1.1);
	img->sy0 = (img->sy0 + y / img->zoom) - y / (img->zoom / 1.1);
	img->zoom /= 1.1;
	img->it_max--;
	return (1);
}
