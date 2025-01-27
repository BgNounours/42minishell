/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:15:47 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/12 12:05:01 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stream.h"
#include <stdlib.h>

t_stream_2	*stream_2_new(const char *str)
{
	t_stream_2	*r;

	r = malloc(sizeof(t_stream_2));
	if (!r)
		return (NULL);
	r->str = str;
	r->i = 0;
	return (r);
}

char	stream_2_getchar(t_stream_2 *stream)
{
	return (stream->str[stream->i]);
}

int	stream_2_next(t_stream_2 *stream)
{
	if (stream_2_continues(stream))
		stream->i++;
	return (stream_2_continues(stream));
}

int	stream_2_continues(t_stream_2 *stream)
{
	if (stream_2_getchar(stream))
		return (1);
	else
		return (0);
}

char	*stream_2_pointer(t_stream_2 *stream)
{
	return ((char *)stream->str + stream->i);
}
