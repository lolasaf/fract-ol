/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wel-safa <wel-safa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 17:06:10 by wel-safa          #+#    #+#             */
/*   Updated: 2023/07/03 17:06:40 by wel-safa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_fd(int n, int fd, int count)
{
	long int	ln;
	char		c;

	ln = n;
	if (fd < 0)
		return (0);
	if (ln < 0)
	{
		ln *= -1;
		write(fd, "-", 1);
		count++;
	}
	if (ln / 10 > 0)
	{
		count = ft_putnbr_fd(ln / 10, fd, count);
		count = ft_putnbr_fd(ln % 10, fd, count);
	}
	if (ln / 10 == 0)
	{
		c = ln + '0';
		write(fd, &c, 1);
		count++;
	}
	return (count);
}

int	ft_putunsignednbr_fd(unsigned int n, int fd, int count)
{
	long unsigned int	ln;
	char				c;

	ln = n;
	if (fd < 0)
		return (0);
	if (ln < 0)
	{
		ln *= -1;
		write(fd, "-", 1);
		count++;
	}
	if (ln / 10 > 0)
	{
		count = ft_putunsignednbr_fd(ln / 10, fd, count);
		count = ft_putunsignednbr_fd(ln % 10, fd, count);
	}
	if (ln / 10 == 0)
	{
		c = ln + '0';
		write(fd, &c, 1);
		count++;
	}
	return (count);
}
