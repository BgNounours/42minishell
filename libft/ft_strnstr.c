/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:50:23 by mcolonna          #+#    #+#             */
/*   Updated: 2023/10/09 16:09:21 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// Return 1 if there is 'little' at the pos 'i' of 'big', or else 0.
static int	match(const char *big, const char *little, size_t len, size_t i)
{
	int	j;

	j = 0;
	while (little[j])
	{
		if (len <= i || big[i] != little[j])
			return (0);
		i++;
		j++;
	}
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (!little[0])
		return ((char *)big);
	if (!big[i] || i >= len)
		return (NULL);
	while (!match(big, little, len, i))
	{
		i++;
		if (!big[i] || i >= len)
			return (NULL);
	}
	return ((char *)big + i);
}
