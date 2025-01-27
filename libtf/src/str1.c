/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:39:04 by mcolonna          #+#    #+#             */
/*   Updated: 2024/04/09 14:05:13 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"
#include "str_utils.h"

int	str_len(t_const_string str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_string	str_dup(t_err err, t_memclass mc, t_const_string str)
{
	t_string	r;
	int			i;

	r = mem_alloc(err, mc, (str_len(str) + 1) * sizeof(char));
	if (!r)
		return (r);
	i = 0;
	while (str[i])
	{
		r[i] = str[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}
