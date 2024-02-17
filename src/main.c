/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:46:34 by wel-safa          #+#    #+#             */
/*   Updated: 2024/02/04 21:34:43 by wel-safa         ###   ########.fr       */
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
	while (++img->px < WIN_SIZE)
	{
		img->py = -1;
		while (++img->py < WIN_SIZE)
			put_pixel_to_img(img, img->px, img->py, 0);
	}
}

void	calc_mandel(t_img *img)
{
	zero_img(img);
	img->px = -1;
	while (++img->px < WIN_SIZE)
	{
		img->py = -1;
		while (++img->py < WIN_SIZE)
		{
			img->sx = img->sx0 + img->px / img->zoom;
			img->sy = img->sy0 + img->py / img->zoom;
			img->it = 0;
			img->x = 0;
			img->y = 0;
			while (img->x * img->x + img->y * img->y <= 4 
				&& img->it < img->it_max)
			{
				img->xtemp = img->x * img->x - img->y * img->y + img->sx;
				img->y = 2 * img->x * img->y + img->sy;
				img->x = img->xtemp;
				img->it++;
			}
			if (img->it == img->it_max)
				put_pixel_to_img(img, img->px, img->py, 0x000000);
			else
				put_pixel_to_img(img, img->px, img->py, img->color * img->it);
		}
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img_ptr, 0, 0);
}

int	exit_win(t_img *img)
{
	mlx_destroy_image(img->mlx, img->img_ptr);
	mlx_destroy_window(img->mlx, img->win);
	// should anything else happen here ??
	exit (1);
}


/*
hooked to event "key press" through mlx_key_hook
int key is the key code pressed
*/
int	keyhook(int key, t_img *data)
{
	if (key == ESC)
		exit_win(data);
	if (key == UP)
		data->sy0 -= 10 / data->zoom;
	if (key == DOWN)
		data->sy0 += 10 / data->zoom;
	if (key == RIGHT)
		data->sx0 += 10 / data->zoom;
	if (key == LEFT)
		data->sx0 -= 10 / data->zoom;
	calc_mandel(data);
	return (0);
}

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
	calc_mandel(img);
	return (0);
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



/*int	main_draft(void)
{
	t_img	img;
	t_vars	vars;

	// initializes the connection between your software and the display	
	vars.mlx = mlx_init();
	
	// creates a window
	vars.win = mlx_new_window(vars.mlx, WIN_SIZE, WIN_SIZE, TITLE);
	if (!vars.win)
	{
		// error
		return (0);
	}
	
	// creates an image
	img.img_ptr = mlx_new_image(vars.mlx, 10, 10);
	
	// retrieves info about image so they can be later modified
	img.addr = mlx_get_data_addr(img.img_ptr, &img.pixel_bits, &img.line_bytes,
		&img.endian);

	// drawing inside a window
	mlx_pixel_put(vars.mlx, vars.win, 5, 5, 0);
	
	// events
	mlx_key_hook(vars.win, keyhook, &vars);
	mlx_mouse_hook(vars.win, mousehook, &vars);

	// loops window until certain events happen
	//mlx_loop_hook(vars.mlx, rendernextframe, &vars);
	next frame is created with vars data
	mlx_loop(vars.mlx);
}
*/

void	init_mandel(t_img *img)
{
	img->zoom = 230;
	img->sx0 = -2.05;
	img->sy0 = -1.3;
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


void	mandelbrot(t_img *img)
{
	init_mandel(img);
	calc_mandel(img);
}

int	main(void)
{
	t_img	img;

	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, WIN_SIZE, WIN_SIZE, "Fract-ol");
	//if (!img.win)
		// error
	img.img_ptr = mlx_new_image(img.mlx, WIN_SIZE, WIN_SIZE);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.pixel_bits,
			&img.line_bytes, &img.endian);
	mlx_key_hook(img.win, keyhook, &img);
	mlx_mouse_hook(img.win, mousehook, &img);
	mlx_hook(img.win, ON_DESTROY, 0, exit_win, &img);
	mandelbrot(&img);
	mlx_loop(img.mlx);
}
