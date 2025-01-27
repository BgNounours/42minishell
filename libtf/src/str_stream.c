/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_stream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 16:17:19 by mcolonna          #+#    #+#             */
/*   Updated: 2024/01/23 18:16:52 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"

char	stream_read(t_stream *stream)
{
	return ((*stream->_read)(&stream->_data));
}

char	stream_pop(t_stream *stream)
{
	return ((*stream->_pop)(&stream->_data));
}
