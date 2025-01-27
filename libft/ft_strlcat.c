/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:40:23 by mcolonna          #+#    #+#             */
/*   Updated: 2023/10/09 16:20:20 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	dest_i;
	size_t	src_i;

	dest_len = min(ft_strlen(dest), size);
	if (dest_len < size - 1)
	{
		dest_i = dest_len;
		src_i = 0;
		while (src[src_i] && size > 0 && dest_i < size - 1)
		{
			dest[dest_i] = src[src_i];
			src_i++;
			dest_i++;
		}
		if (size > 0)
			dest[dest_i] = '\0';
	}
	return (dest_len + ft_strlen(src));
}
