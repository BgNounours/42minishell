/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:15:47 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/12 12:06:27 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stream.h"

void	stream_2_skip(t_stream_2 *stream, int n)
{
	while (n-- && stream_2_continues(stream))
		stream_2_next(stream);
}
