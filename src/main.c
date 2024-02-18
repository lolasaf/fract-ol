/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 18:46:34 by wel-safa          #+#    #+#             */
/*   Updated: 2024/02/18 20:56:30 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	printerror(void)
{
	ft_printf("Parameter structure = <fractal type> <parameters if any>\n");
	ft_printf("Allowed inputs: \nmandel\nor\njulia a b\n");
	ft_printf("where a & b are float numbers in the form xxxxxx.xxxxxx\n");
	ft_printf("such as a = Re(c) and b = Im(c)\n");
	ft_printf("in polynommial f(z) = z^2 + c\n");
	exit(1);
}

void	ft_datoi_2(const char *nptr, long double *res, size_t *i)
{
	long double	dec;

	while (nptr[*i] >= '0' && nptr[*i] <= '9' && nptr[*i])
	{
		*res = *res * 10.0 + (nptr[*i] - '0');
		(*i)++;
	}
	if (nptr[*i] == '.')
	{
		dec = 10;
		(*i)++;
		while (nptr[*i] >= '0' && nptr[*i] <= '9' && nptr[*i])
		{
			*res = *res + (nptr[*i] - '0') / dec;
			dec *= 10;
			(*i)++;
		}
	}
	if (nptr[*i])
		printerror();
	else if (nptr[*i - 1] == '.')
		printerror();
}

double	ft_datoi(const char *nptr)
{
	size_t			i;
	long double		sign;
	long double		res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] == ' ' || (nptr[i] >= '\t' && nptr[i] <= '\r'))
		i++;
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	if (nptr[i] >= '0' && nptr[i] <= '9')
		ft_datoi_2(nptr, &res, &i);
	else
		printerror();
	return (res * sign);
}

void	main_init(int argc, char **argv, t_img *img)
{
	if (!ft_strncmp(argv[1], "mandel", 100))
	{
		if (argc == 2)
			img->type = MANDEL;
		else
			printerror();
	}
	else if (!ft_strncmp(argv[1], "julia", 100))
	{
		if (argc == 4)
		{
			img->type = JULIA;
			img->a = ft_datoi(argv[2]);
			img->b = ft_datoi(argv[3]);
		}
		else
			printerror();
	}
	else
		printerror();
}

int	main(int argc, char **argv)
{
	t_img	img;

	if (argc == 1)
		printerror();
	main_init(argc, argv, &img);
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, WIN_WIDTH, WIN_HEIGHT, "Fract-ol");
	if (!img.win)
		exit_win(&img);
	img.img_ptr = mlx_new_image(img.mlx, WIN_WIDTH, WIN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.pixel_bits,
			&img.line_bytes, &img.endian);
	mlx_key_hook(img.win, keyhook, &img);
	mlx_mouse_hook(img.win, mousehook, &img);
	mlx_hook(img.win, ON_DESTROY, 0, exit_win, &img);
	if (img.type == MANDEL)
		mandelbrot(&img);
	else if (img.type == JULIA)
		filledjulia(&img);
	mlx_loop(img.mlx);
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
