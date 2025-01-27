/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_char1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 13:09:35 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/13 13:29:59 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"

bool	char_isin(char c, t_const_string charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (true);
		i++;
	}
	return (false);
}

bool	char_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	char_isupper(char c)
{
	return (c >= 'A' && c <= 'Z');
}

bool	char_islower(char c)
{
	return (c >= 'a' && c <= 'z');
}

bool	char_isalpha(char c)
{
	return (char_isupper(c) || char_islower(c));
}
