/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:47:40 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/27 14:21:20 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "parse_command_utils.h"

int	parse_error(const char *msg)
{
	print_str(fatal_error, 2, "parse error: ");
	print_line(fatal_error, 2, msg);
	return (1);
}

void	skip_blank(t_stream *stream)
{
	stream_skip(stream, " \r\n\t");
}

// Add 'c' at the end of 'str' and return the result.
// Also mem_free() 'str'.
static char	*str_addchar(t_memclass mc, const char *str, char c)
{
	char	*s;
	char	*r;

	s = str_dup(fatal_error, mc, "-");
	s[0] = c;
	r = str_join(fatal_error, mc, str, s);
	mem_free(s);
	mem_free((void *)str);
	return (r);
}

void	read_until(t_parsing_args *args, const char **dest,
				const char *stop_charset)
{
	while (stream_read(&args->stream)
		&& !char_isin(stream_read(&args->stream), stop_charset)
	)
		*dest = str_addchar(args->mc, *dest, stream_pop(&args->stream));
}

void	read_only(t_parsing_args *args, const char **dest, const char *charset)
{
	while (char_isin(stream_read(&args->stream), charset))
		*dest = str_addchar(args->mc, *dest, stream_pop(&args->stream));
}
