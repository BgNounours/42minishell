/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:28:19 by mcolonna          #+#    #+#             */
/*   Updated: 2024/03/25 14:45:18 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"
#include "read_line_utils.h"

int	create_empty_buf(t_buf **result)
{
	const t_errmc		errmc = setget_errmc(NULL, NULL);
	const t_memclass	mc = mem_newclass(errmc.err);

	*result = mem_alloc(errmc.err, mc, sizeof(t_buf));
	if (!*result)
		return (0);
	(*result)->size = 0;
	(*result)->mc = mc;
	return (1);
}

int	create_empty_string(t_string2 **result)
{
	const t_errmc	errmc = setget_errmc(NULL, NULL);

	*result = mem_alloc(errmc.err, errmc.mc, sizeof(t_string2));
	if (!*result)
		return (0);
	(*result)->str = mem_alloc(errmc.err, errmc.mc, sizeof(char));
	if (!(*result)->str)
	{
		mem_free(*result);
		return (0);
	}
	(*result)->size = 0;
	return (1);
}

int	append_to_string(t_string2 *string, char *to_append, int to_append_size)
{
	char			*new_str;
	int				i;
	const t_errmc	errmc = setget_errmc(NULL, NULL);

	new_str = mem_alloc(errmc.err, errmc.mc,
			(string->size + to_append_size) * sizeof(char));
	if (!new_str)
		return (-1);
	i = -1;
	while (++i < string->size)
		new_str[i] = string->str[i];
	i = -1;
	while (++i < to_append_size)
		new_str[i + string->size] = to_append[i];
	mem_free(string->str);
	string->str = new_str;
	string->size += to_append_size;
	return (1);
}

void	free_string(t_string2 **string)
{
	mem_free((*string)->str);
	mem_free(*string);
	*string = NULL;
}

t_errmc	setget_errmc(t_err err, t_memclass mc)
{
	static t_err		*err_v = NULL;
	static t_memclass	mc_v = NULL;
	t_errmc				r;

	if (err && mc)
	{
		err_v = err;
		mc_v = mc;
	}
	r.err = err_v;
	r.mc = mc_v;
	return (r);
}
