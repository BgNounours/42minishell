/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:41:02 by mcolonna          #+#    #+#             */
/*   Updated: 2023/10/09 15:58:33 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;
	int		len;

	if ((long)nmemb * (long)size > (long)INT_MAX)
		return (NULL);
	len = size * nmemb;
	dest = malloc(len);
	if (!dest)
		return (NULL);
	ft_bzero(dest, len);
	return (dest);
}
