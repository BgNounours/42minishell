/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:53:07 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/12 13:25:57 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "conversions.h"
#include "utils.h"
#include "libtf.h"
#include <unistd.h>

int	put_char(va_list args)
{
	const char	c = va_arg(args, int);

	write(1, &c, 1);
	return (1);
}

int	put_str(va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	write(1, str, str_len(str));
	return (str_len(str));
}

int	put_percent(va_list args)
{
	(void)args;
	write(1, "%", 1);
	return (1);
}

int	put_decimal(va_list args)
{
	char	*str;
	int		r;
	int		arg;

	arg = va_arg(args, int);
	str = ft_itoa(arg);
	if (!str)
		return (-1);
	write(1, str, str_len(str));
	r = str_len(str);
	free(str);
	return (r);
}

int	put_unsigned(va_list args)
{
	char	*str;
	int		r;

	str = ft_utoa(va_arg(args, unsigned int));
	if (!str)
		return (-1);
	write(1, str, str_len(str));
	r = str_len(str);
	free(str);
	return (r);
}
