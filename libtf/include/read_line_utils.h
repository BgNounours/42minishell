/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:36:49 by mcolonna          #+#    #+#             */
/*   Updated: 2024/03/25 14:21:52 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_LINE_UTILS_H
# define READ_LINE_UTILS_H

# include "libtf.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# define NB_FILE_DESCRIPTORS 4096

typedef struct s_buf
{
	t_memclass	mc;
	int			size;
	char		str[BUFFER_SIZE];
}				t_buf;

typedef struct s_string2
{
	int		size;
	char	*str;
}			t_string2;

typedef struct s_errmc
{
	t_err		*err;
	t_memclass	mc;
}				t_errmc;

// NULL if error.
// Return a pointer to free. Nothing if error.
int			create_empty_buf(t_buf **result);

// -1 if error, or else 1.
// string->str will be freed, the new string->str will be to free.
// If error, no free or malloc is done.
int			append_to_string(
				t_string2 *string, char *to_append, int to_append_size);

// Return 0 if error, or else 1.
// *result (and its "str" value) to free. Nothing to free if error.
int			create_empty_string(t_string2 **result);

// Free string->str and string.
void		free_string(t_string2 **string);

t_errmc		setget_errmc(t_err err, t_memclass mc);

#endif
