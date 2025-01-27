/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:26:46 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/12 12:59:05 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libtf.h"
#include "unistd.h"
#include <stdlib.h>

char	*ft_utoa(unsigned int n)
{
	char	first_digit[2];
	char	*tmp;
	char	*r;

	if (n >= 1000000000)
		first_digit[0] = n / 1000000000 + '0';
	else
		first_digit[0] = '\0';
	first_digit[1] = '\0';
	tmp = ft_itoa(n % 1000000000);
	if (!tmp)
		return (NULL);
	r = ft_strjoin(first_digit, tmp);
	free(tmp);
	return (r);
}

static char	get_digit_at(
		unsigned long n, int i, int nb_len, const char *base)
{
	int			w;
	long long	base_power;
	const int	base_len = str_len(base);

	w = nb_len - i - 1;
	base_power = 1;
	while (w--)
		base_power *= base_len;
	return (base[n / base_power % base_len]);
}

static int	get_nb_len(unsigned long n, const char *base)
{
	int					r;
	const int			base_len = str_len(base);

	r = 0;
	while (n > 0)
	{
		n /= (unsigned long long)base_len;
		r++;
	}
	if (r == 0)
		r = 1;
	return (r);
}

char	*ft_utoa_base(unsigned long n, const char *base)
{
	int		nb_len;
	char	*dest;
	int		i;

	nb_len = get_nb_len(n, base);
	dest = malloc((nb_len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < nb_len)
	{
		dest[i] = get_digit_at(n, i, nb_len, base);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
