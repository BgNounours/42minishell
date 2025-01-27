/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:39:50 by mcolonna          #+#    #+#             */
/*   Updated: 2024/03/25 14:29:49 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libtf.h"
#include "read_line_utils.h"

// If *eol is set to:
// - 1, that means the line is ended with a '\n'.
// - 0, no '\n' found, buf is now empty.
// If error, returns -1 or else returns 1.
static int	pop_until_line_break(int *eol, t_string2 *line, t_buf *buf)
{
	int	i1;
	int	i2;

	*eol = 0;
	i1 = 0;
	while (!*eol && i1 < buf->size)
	{
		if (buf->str[i1] == '\n')
			*eol = 1;
		i1++;
	}
	if (append_to_string(line, buf->str, i1) == -1)
		return (-1);
	i2 = 0;
	while (i2 < buf->size - i1)
	{
		buf->str[i2] = buf->str[i2 + i1];
		i2++;
	}
	buf->size -= i1;
	return (1);
}

// Returns -1 if error, or else 1.
static int	fill_buf(int *eof, t_buf *buf, int fd)
{
	int				r;
	const t_errmc	errmc = setget_errmc(NULL, NULL);

	*eof = 0;
	r = read(fd, buf->str, BUFFER_SIZE);
	if (r == -1)
		return (errmc.err("errno"), -1);
	buf->size += r;
	if (!r)
		*eof = 1;
	return (1);
}

// Free things and returns to_return.
static void	*free_and_return(
				void *to_return, t_buf **buf, t_string2 **string, void *any)
{
	if (buf)
	{
		mem_freeall((*buf)->mc);
		*buf = NULL;
	}
	if (string)
		free_string(string);
	mem_free(any);
	return (to_return);
}

t_const_string	read_line(t_err err, t_memclass mc, int fd)
{
	static t_buf	*bufs[NB_FILE_DESCRIPTORS];
	t_string2		*line;
	int				eofeol[2];

	setget_errmc(err, mc);
	if (fd >= NB_FILE_DESCRIPTORS || fd < 0)
		return (err("bad value"), NULL);
	if (!bufs[fd] && !create_empty_buf(&bufs[fd]))
		return (NULL);
	if (!create_empty_string(&line))
		return (free_and_return(NULL, &bufs[fd], NULL, NULL));
	eofeol[0] = 0;
	eofeol[1] = 0;
	while (!eofeol[0])
	{
		if (pop_until_line_break(&eofeol[1], line, bufs[fd]) == -1)
			return (free_and_return(NULL, &bufs[fd], &line, NULL));
		if (eofeol[1])
			break ;
		if (fill_buf(&eofeol[0], bufs[fd], fd) == -1)
			return (free_and_return(NULL, &bufs[fd], &line, NULL));
	}
	if (append_to_string(line, "", 1) == 1 && line->size > 1)
		return (free_and_return(line->str, NULL, NULL, line));
	return (free_and_return(NULL, &bufs[fd], &line, NULL));
}
