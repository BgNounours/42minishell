/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_read_string.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:47:40 by mcolonna          #+#    #+#             */
/*   Updated: 2024/07/03 12:08:12 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "parse_command_utils.h"

// Read the value of the variable and append it to dest.
// The stream must point to the first char of the variable name.
// Write a parse error and change args->r.error if no variable name.
static void	read_variable_value(t_parsing_args *args, const char **dest)
{
	const char	*name;
	const char	*value;
	const char	*tmp;

	name = NULL;
	if (stream_read(&args->stream) == '?')
	{
		stream_pop(&args->stream);
		value = str_inttostr(fatal_error, args->mc, args->env->errorstatus);
	}
	else
	{
		name = str_dup(fatal_error, args->mc, "");
		read_only(args, &name, SYMBOL_CHARS);
		if (str_eq(name, ""))
		{
			args->r.error = parse_error("variable name expected");
			return ;
		}
		value = variables_get(args->variables, name);
	}
	tmp = *dest;
	*dest = str_join(fatal_error, args->mc, *dest, value);
	mem_free((char *)name);
	mem_free((char *)tmp);
}

// Read a string without quotes.
// Append it to dest.
// Change args->r.error if error.
static void	read_string_noquote(t_parsing_args *args, const char **dest,
				const char *stop_charset)
{
	const char	*real_stop_charset
		= str_join(fatal_error, args->mc, stop_charset, "$\"'");

	while (stream_read(&args->stream)
		&& !char_isin(stream_read(&args->stream), stop_charset)
		&& !char_isin(stream_read(&args->stream), "\"'"))
	{
		read_until(args, dest, real_stop_charset);
		if (stream_read(&args->stream) == '$')
		{
			stream_pop(&args->stream);
			read_variable_value(args, dest);
			if (args->r.error)
				return ;
		}
	}
}

// Read a string with ' quotes.
// Append it to dest.
// Return false if it is not a ' quoted string.
// If parse error, return true and change args.r.error accordingly.
static bool	read_string_quote(t_parsing_args *args, const char **dest)
{
	if (stream_read(&args->stream) != '\'')
		return (false);
	stream_pop(&args->stream);
	read_until(args, dest, "'");
	if (!stream_read(&args->stream))
	{
		args->r.error = parse_error("EOF unexpected");
		return (true);
	}
	stream_pop(&args->stream);
	return (true);
}

// Read a string with " quotes.
// Append it to dest.
// Return false if it is not a " quoted string.
// If parse error, return true and change args.r.error accordingly.
static bool	read_string_doublequote(t_parsing_args *args, const char **dest)
{
	if (stream_read(&args->stream) != '"')
		return (false);
	stream_pop(&args->stream);
	while (stream_read(&args->stream) && stream_read(&args->stream) != '"')
	{
		read_until(args, dest, "\"$");
		if (stream_read(&args->stream) == '$')
		{
			stream_pop(&args->stream);
			read_variable_value(args, dest);
			if (args->r.error)
				return (true);
		}
	}
	if (!stream_read(&args->stream))
	{
		args->r.error = parse_error("EOF unexpected");
		return (true);
	}
	stream_pop(&args->stream);
	return (true);
}

// Read the string, stop if the char is in stop_charset.
// Syntax: /([^{stop_charset}]|'.*'|".*")+/
// Change args->r.error and return NULL if error.
const char	*read_string(t_parsing_args *args, const char *stop_charset)
{
	const char	*str;
	char *const	real_stop_charset
		= str_join(fatal_error, args->mc, stop_charset, " \r\n\t");

	if (!stream_read(&args->stream))
		return (NULL);
	str = str_dup(fatal_error, args->mc, "");
	while (!args->r.error
		&& stream_read(&args->stream)
		&& !char_isin(stream_read(&args->stream), real_stop_charset))
	{
		if (!read_string_quote(args, &str)
			&& !read_string_doublequote(args, &str))
			read_string_noquote(args, &str, real_stop_charset);
	}
	mem_free(real_stop_charset);
	if (args->r.error)
		return (NULL);
	return (str);
}
