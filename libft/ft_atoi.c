/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 17:45:41 by mcolonna          #+#    #+#             */
/*   Updated: 2023/10/09 12:03:52 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_in(char c, char *chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		if (c == chars[i])
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	i;
	int	r;

	sign = 1;
	i = 0;
	r = 0;
	while (is_in(nptr[i], " \f\n\r\t\v"))
		i++;
	if (is_in(nptr[i], "+-"))
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (is_in(nptr[i], "0123456789"))
	{
		r = r * 10 + (nptr[i] - '0');
		i++;
	}
	return (r * sign);
}
