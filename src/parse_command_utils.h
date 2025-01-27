/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:47:40 by mcolonna          #+#    #+#             */
/*   Updated: 2024/07/03 11:33:12 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_COMMAND_UTILS_H
# define PARSE_COMMAND_UTILS_H

# include "include.h"

// Global variables for all the parsing functions
typedef struct s_parsing_args
{
	t_memclass	mc;
	t_command	r;
	t_stream	stream;
	t_list		calls;
	bool		got_first_call;
	const char	*heredoc;
	t_list		*variables;
	t_env		*env;
}			t_parsing_args;

// To call when a parse error occurs.
// Always returns 1 (parse error's status).
int		parse_error(const char *msg);

// Skip blank characters
void	skip_blank(t_stream *stream);

// Read until a character is in the charset or is '\0'
// and append the string to dest.
void	read_until(t_parsing_args *args, const char **dest,
			const char *stop_charset);

// Read until a character isn't in the charset or is '\0'
// and append the string to dest.
void	read_only(t_parsing_args *args, const char **dest, const char *charset);

#endif
