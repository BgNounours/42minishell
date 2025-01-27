/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_stream_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:48:47 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/13 17:07:24 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"
#include <limits.h>

void	stream_skip(t_stream *stream, t_const_string charset)
{
	while (stream_read(stream)
		&& char_isin(stream_read(stream), charset))
		stream_pop(stream);
}

unsigned int	stream_readuint(t_err *err, t_stream *stream)
{
	unsigned long	r;

	if (!char_isdigit(stream_read(stream)))
		return ((*err)("bad value"), 0);
	r = 0;
	while (char_isdigit(stream_read(stream)))
	{
		r *= 10;
		r += stream_pop(stream) - '0';
		if (r > UINT_MAX)
			return ((*err)("bad value"), 0);
	}
	return ((unsigned int)r);
}

int	stream_readint(t_err *err, t_stream *stream)
{
	unsigned int	abs;
	bool			negative;

	negative = false;
	if (char_isin(stream_read(stream), "-+"))
	{
		if (stream_read(stream) == '-')
			negative = true;
		stream_pop(stream);
	}
	abs = stream_readuint(&err_remember, stream);
	if (err_get())
		return ((*err)("bad value"), -1);
	if (negative && -(long)abs >= INT_MIN)
		return ((int)-abs);
	if (!negative && (long)abs <= INT_MAX)
		return ((int)abs);
	return ((*err)("bad value"), -1);
}
