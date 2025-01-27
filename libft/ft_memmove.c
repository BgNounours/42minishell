/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:17:41 by mcolonna          #+#    #+#             */
/*   Updated: 2023/10/12 10:44:37 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;

	if (!dest || !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (dest < src)
			((char *)dest)[i] = ((char *)src)[i];
		else
			((char *)dest)[n - i - 1] = ((char *)src)[n - i - 1];
		i++;
	}
	return (dest);
}
