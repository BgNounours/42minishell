/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_streamstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:09:37 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/12 17:07:35 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"

static char	streamstr_pop(const void **data)
{
	char	r;

	r = **(char **)data;
	if (r)
		(*(char **)data)++;
	return (r);
}

static char	streamstr_read(const void **data)
{
	return (**(char **)data);
}

t_stream	*streamstr_alloc(t_err err, t_memclass mc, t_const_string str)
{
	t_stream		*r;

	r = mem_alloc(err, mc, sizeof(t_stream));
	if (!r)
		return (NULL);
	streamstr_init(r, str);
	return (r);
}

void	streamstr_init(t_stream *stream, t_const_string str)
{
	stream->_read = &streamstr_read;
	stream->_pop = &streamstr_pop;
	stream->_data = str;
}
