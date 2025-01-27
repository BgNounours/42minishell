/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 13:39:04 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/23 11:36:07 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"
#include "str_utils.h"

static t_two_strings	two_strings(t_const_string str, t_const_string charset)
{
	t_two_strings	r;

	r.str = str;
	r.charset = charset;
	return (r);
}

static t_string	get_word_at_index(
	t_err *err, t_memclass mc, int index, t_two_strings args)
{
	int			i;
	int			j;
	t_string	r;

	i = 0;
	while (char_isin(args.str[i], args.charset))
		i++;
	while (--index >= 0)
	{
		while (args.str[i] && !char_isin(args.str[i], args.charset))
			i++;
		while (char_isin(args.str[i], args.charset))
			i++;
	}
	j = 0;
	while (args.str[i + j] && !char_isin(args.str[i + j], args.charset))
		j++;
	r = mem_alloc(err, mc, (j + 1) * sizeof(char));
	if (!r)
		return (NULL);
	r[j] = '\0';
	while (--j >= 0)
		r[j] = args.str[i + j];
	return (r);
}

static int	count_words(t_const_string str, t_const_string charset)
{
	t_stream		stream;
	int				r;

	streamstr_init(&stream, str);
	r = 0;
	while (stream_read(&stream))
	{
		stream_skip(&stream, charset);
		if (stream_read(&stream))
		{
			r++;
			while (stream_read(&stream)
				&& !char_isin(stream_read(&stream), charset))
				stream_pop(&stream);
		}
	}
	return (r);
}

t_string	*str_split(
	t_err err, t_memclass mc, t_const_string str, t_const_string charset)
{
	t_stream	stream;
	t_string	*r;
	int			i;

	i = count_words(str, charset);
	r = mem_alloc(err, mc, (i + 1) * sizeof(t_string));
	if (!r)
		return (NULL);
	streamstr_init(&stream, str);
	r[i] = NULL;
	while (--i >= 0)
	{
		r[i] = get_word_at_index(err, mc, i, two_strings(str, charset));
		if (!r[i])
			return (NULL);
	}
	return (r);
}

bool	str_eq(t_const_string str1, t_const_string str2)
{
	int	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	return (str1[i] == str2[i]);
}
