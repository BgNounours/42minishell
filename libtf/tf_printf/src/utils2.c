/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:26:46 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/12 12:06:57 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "stream.h"
#include "unistd.h"
#include <stdlib.h>

static int	is_in(char c, char *chars)
{
	int	i;

	i = 0;
	while (chars[i])
	{
		if (c == chars[i])
			return (1);
		i++;
	}
	return (0);
}

unsigned int	stream_2_atoi(t_stream_2 *stream)
{
	int	r;

	r = 0;
	while (is_in(stream_2_getchar(stream), "0123456789"))
	{
		r = r * 10 + (stream_2_getchar(stream) - '0');
		stream_2_next(stream);
	}
	return (r);
}
