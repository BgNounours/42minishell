/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:43:17 by mcolonna          #+#    #+#             */
/*   Updated: 2023/10/10 13:16:58 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*r;
	int		i;

	r = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			r = (char *)s + i;
		i++;
	}
	if (s[i] == c)
		r = (char *)s + i;
	return (r);
}
