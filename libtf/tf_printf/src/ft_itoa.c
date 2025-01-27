/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:51:10 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/12 12:13:37 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	get_digit_at(long pos_n, int i, int nb_len)
{
	int		w;
	long	ten_power;

	w = nb_len - i - 1;
	ten_power = 1;
	while (w--)
		ten_power *= 10;
	return ('0' + pos_n / ten_power % 10);
}

static int	get_nb_len(long pos_n)
{
	int		r;
	long	ten_powers;

	r = 1;
	ten_powers = 10;
	while (pos_n >= ten_powers)
	{
		r++;
		ten_powers *= 10;
	}
	return (r);
}

char	*ft_itoa(int n)
{
	long	pos_n;
	int		sign;
	int		nb_len;
	char	*dest;
	int		i;

	sign = (n >= 0) - (n < 0);
	pos_n = (long)n * sign;
	nb_len = get_nb_len(pos_n);
	dest = malloc(((sign == -1) + nb_len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	if (sign == -1)
		dest[i++] = '-';
	while (i - (sign == -1) < nb_len)
	{
		dest[i] = get_digit_at(pos_n, i - (sign == -1), nb_len);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
