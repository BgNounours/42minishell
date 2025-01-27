/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:47:18 by mcolonna          #+#    #+#             */
/*   Updated: 2023/10/12 13:24:04 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	count_until(char const *s, char const c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	count_words(char const *s, char c)
{
	int	i;
	int	r;
	int	in_a_word;

	i = 0;
	r = 0;
	in_a_word = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			in_a_word = 0;
		}
		else if (!in_a_word)
		{
			in_a_word = 1;
			r++;
		}
		i++;
	}
	return (r);
}

static char	**free_array(char ***array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free((*array)[i]);
		(*array)[i] = NULL;
		i++;
	}
	free(*array);
	*array = NULL;
	return (NULL);
}

static void	ignore_sep(char const *s, char c, int *i)
{
	while (s[*i] == c)
		(*i)++;
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**dest;
	int		i;
	int		str_i;
	int		len_until;

	size = count_words(s, c);
	dest = malloc((size + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	i = -1;
	str_i = 0;
	while (++i < size)
	{
		ignore_sep(s, c, &str_i);
		len_until = count_until(s + str_i, c);
		dest[i] = ft_substr(s, str_i, len_until);
		if (!dest[i])
			return (free_array(&dest, i));
		str_i += len_until;
	}
	dest[i] = NULL;
	return (dest);
}
