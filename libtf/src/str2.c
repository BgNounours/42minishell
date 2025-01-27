/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:19:37 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/15 11:12:22 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"

unsigned int	str_touint(t_err err, t_const_string str)
{
	t_stream		stream;
	unsigned int	r;

	streamstr_init(&stream, str);
	r = stream_readuint(&err_remember, &stream);
	if (err_get() || stream_read(&stream))
		return ((*err)("bad value"), 0);
	return (r);
}

int	str_toint(t_err err, t_const_string str)
{
	t_stream	stream;
	int			r;

	streamstr_init(&stream, str);
	r = stream_readint(&err_remember, &stream);
	if (err_get() || stream_read(&stream))
		return ((*err)("bad value"), -1);
	return (r);
}

t_string	str_join(t_err *err, t_memclass mc, t_const_string str1,
						t_const_string str2)
{
	const size_t	len1 = str_len(str1);
	const size_t	len2 = str_len(str2);
	t_string		r;

	r = mem_alloc(err, mc, sizeof(char) * (len1 + len2 + 1));
	if (!r)
		return (NULL);
	data_cpy(r, str1, len1);
	data_cpy(r + len1, str2, len2);
	r[len1 + len2] = '\0';
	return (r);
}

t_string	str_uinttostr(t_err *err, t_memclass mc, unsigned int n)
{
	const t_const_string	digits[] = {
		"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
	t_string				r;
	t_string				tmp;

	if (n == 0)
		return (str_dup(err, mc, "0"));
	r = str_dup(err, mc, digits[n % 10]);
	n /= 10;
	while (n > 0)
	{
		tmp = r;
		r = str_join(err, mc, digits[n % 10], r);
		mem_free(tmp);
		n /= 10;
	}
	return (r);
}

t_string	str_inttostr(t_err *err, t_memclass mc, int n)
{
	t_string	r;

	if (n >= 0)
		return (str_uinttostr(err, mc, n));
	else
	{
		r = str_uinttostr(err, mc, -n);
		if (!r)
			return (NULL);
		return (str_join(err, mc, "-", r));
	}
}
