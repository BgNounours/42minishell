/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:39:33 by mcolonna          #+#    #+#             */
/*   Updated: 2023/10/04 13:07:54 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_in(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	get_length(char const *s1, char const *set)
{
	size_t	i;
	size_t	r;
	size_t	tmp;

	i = 0;
	while (is_in(s1[i], set))
		i++;
	r = 0;
	tmp = 0;
	while (s1[i])
	{
		if (is_in(s1[i], set))
		{
			tmp++;
		}
		else
		{
			r += tmp;
			tmp = 0;
			r++;
		}
		i++;
	}
	return (r);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*dest;
	size_t	start;
	size_t	i;

	len = get_length(s1, set);
	dest = malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	start = 0;
	while (is_in(s1[start], set))
		start++;
	i = 0;
	while (i < len)
	{
		dest[i] = s1[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
