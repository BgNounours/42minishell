/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tf_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:07:21 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/12 12:36:08 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tf_printf.h"
#include "stream.h"
#include "do_conversion.h"
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

// Print the escaped string (with %) from str at i.
// str[i] must be a '%'.
// Return the number of chars wrote.
// Return a negative value if error.
static int	print_esc(va_list args, t_stream_2 *stream)
{
	int		r;

	stream_2_next(stream);
	r = do_conversion(args, stream_2_getchar(stream));
	stream_2_next(stream);
	return (r);
}

// Count the number of chars until a '%' or the end of the string.
static int	txt_len(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '%')
		i++;
	return (i);
}

int	tf_printf(const char *str, ...)
{
	va_list		args;
	t_stream_2	*stream;
	int			count;
	int			len;

	va_start(args, str);
	stream = stream_2_new(str);
	if (!stream)
		return (-1);
	count = 0;
	while (stream_2_continues(stream))
	{
		len = txt_len(stream_2_pointer(stream));
		write(1, stream_2_pointer(stream), len);
		stream_2_skip(stream, len);
		count += len;
		if (!stream_2_getchar(stream))
			break ;
		len = print_esc(args, stream);
		if (len == -1)
			return (free(stream), -1);
		count += len;
	}
	return (free(stream), count);
}
