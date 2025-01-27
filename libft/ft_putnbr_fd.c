/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:32:29 by mcolonna          #+#    #+#             */
/*   Updated: 2023/10/09 17:23:02 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include "libft.h"

static void	putunsigned(long nb, int fd)
{
	if (nb == 0)
		return ;
	putunsigned(nb / 10, fd);
	ft_putchar_fd((char)(nb % 10) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nb = -(long)n;
	}
	else
		nb = n;
	if (n == 0)
		ft_putchar_fd('0', fd);
	else
		putunsigned(nb, fd);
}
