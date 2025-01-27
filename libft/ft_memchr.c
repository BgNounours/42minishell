/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:28:00 by mcolonna          #+#    #+#             */
/*   Updated: 2023/10/03 15:31:16 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*s2 = s;

	i = 0;
	while (i < n)
	{
		if (s2[i] == (char) c)
			return ((void *) s + i);
		i++;
	}
	return (NULL);
}
