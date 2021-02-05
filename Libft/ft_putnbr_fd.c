/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunyoo <hyunyoo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 10:27:33 by hyunyoo           #+#    #+#             */
/*   Updated: 2020/07/11 12:03:22 by hyunyoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putnbr(int n, int fd)
{
	if (n / 10)
	{
		putnbr(n / 10, fd);
		putnbr(n % 10, fd);
	}
	else if (n > 0)
		ft_putchar_fd('0' + (char)n, fd);
	else
		ft_putchar_fd('0' + -(char)n, fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
		ft_putchar_fd('-', fd);
	putnbr(n, fd);
}
