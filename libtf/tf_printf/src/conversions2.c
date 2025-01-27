/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:21:09 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/12 12:58:11 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversions.h"
#include "utils.h"
#include "libtf.h"
#include <unistd.h>

int	put_hex_lower(va_list args)
{
	char	*str;
	int		r;

	r = 0;
	str = ft_utoa_base(va_arg(args, unsigned int), "0123456789abcdef");
	if (!str)
		return (-1);
	write(1, str, str_len(str));
	r += str_len(str);
	free(str);
	return (r);
}

int	put_hex_upper(va_list args)
{
	char	*str;
	int		r;

	r = 0;
	str = ft_utoa_base(va_arg(args, unsigned int), "0123456789ABCDEF");
	if (!str)
		return (-1);
	write(1, str, str_len(str));
	r += str_len(str);
	free(str);
	return (r);
}

int	put_pointer(va_list args)
{
	void	*arg;
	char	*str;
	int		r;

	arg = va_arg(args, void *);
	if (!arg)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	str = ft_utoa_base((unsigned long)arg, "0123456789abcdef");
	if (!str)
		return (-1);
	write(1, str, str_len(str));
	r = 2 + str_len(str);
	free(str);
	return (r);
}
