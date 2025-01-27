/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_read_element.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:47:40 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/27 14:42:34 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "parse_command_read_string.h"
#include "parse_command_read_element.h"

// Get a program call (program names & its arguments) until stop_charset.
// Change args accordingly.
// On success, return 0. On error, return the error status.
static int	read_call(t_parsing_args *args, const char *stop_charset)
{
	t_call		*r;
	t_list		arguments;
	const char	*str;

	arguments = list_createempty(args->mc);
	while (stream_read(&args->stream)
		&& !char_isin(stream_read(&args->stream), stop_charset))
	{
		str = read_string(args, stop_charset);
		if (args->r.error)
			return (args->r.error);
		if (!str)
			return (parse_error("EOF unexpected"));
		list_add(fatal_error, &arguments, (char *)str);
		skip_blank(&args->stream);
	}
	r = mem_alloc(fatal_error, args->mc, sizeof(t_call));
	r->program = (char *)list_get(err_remember, &arguments, 0);
	if (err_get())
		return (parse_error("program name expected"));
	r->argc = list_getsize(&arguments);
	r->argv = (char *const *)list_convert(fatal_error, args->mc, &arguments);
	list_add(fatal_error, &args->calls, (t_call *)r);
	args->got_first_call = true;
	return (0);
}

// Read a '<' or '<<' redirection from the file.
// Change args accordingly.
// On success, return 0. On error, return the error status.
static int	read_inputfile(t_parsing_args *args, const char *stop_charset)
{
	const char	*str;
	bool		heredoc;

	if (args->r.input_fd != 0)
		return (parse_error("several input files"));
	if (!stream_read(&args->stream))
		return (parse_error("EOF unexpected"));
	heredoc = stream_read(&args->stream) == '<';
	if (heredoc)
		stream_pop(&args->stream);
	skip_blank(&args->stream);
	str = read_string(args, stop_charset);
	if (args->r.error)
		return (args->r.error);
	if (!str)
		return (parse_error("EOF unexpected"));
	if (heredoc)
		args->heredoc = str;
	else
	{
		args->r.input_fd = open(str, O_RDONLY);
		if (args->r.input_fd == -1)
			return (perror(str), errno);
	}
	return (0);
}

// Read a '>' or '>>' redirection from the file.
// Change args accordingly.
// On success, return 0. On error, return the error status.
static int	read_outputfile(t_parsing_args *args, const char *stop_charset)
{
	const char	*str;
	int			flag;

	if (args->r.output_fd != 1)
		return (parse_error("several output files"));
	if (!stream_read(&args->stream))
		return (parse_error("EOF unexpected"));
	flag = O_TRUNC;
	if (stream_read(&args->stream) == '>')
	{
		stream_pop(&args->stream);
		flag = O_APPEND;
	}
	skip_blank(&args->stream);
	str = read_string(args, stop_charset);
	if (args->r.error)
		return (args->r.error);
	if (!str)
		return (parse_error("EOF unexpected"));
	args->r.output_fd = open(
			str, O_WRONLY | O_CREAT | flag, 0666);
	if (args->r.output_fd == -1)
		return (perror(str), errno);
	return (0);
}

// (extension of read_element)
static void	read_element2(t_parsing_args *args, int *error, char c)
{
	stream_pop(&args->stream);
	skip_blank(&args->stream);
	if (c == '|')
	{
		if (!args->got_first_call)
			*error = parse_error("pipe before any call to a program");
		else
			*error = read_call(args, "<>|");
	}
	else if (c == '>')
		*error = read_outputfile(args, "<>|");
	else if (c == '<')
		*error = read_inputfile(args, "<>|");
	else
		fatal_error_msg("internal error u.u");
}

// Read an element from the stream (a call to a program or a redirection)
// Change args accordingly.
// On success, return 0. On error, return the error status.
int	read_element(t_parsing_args *args)
{
	char							c;
	int								error;

	error = 0;
	while (!error && stream_read(&args->stream))
	{
		c = stream_read(&args->stream);
		if (char_isin(c, "|><"))
			read_element2(args, &error, c);
		else if (!args->got_first_call)
			error = read_call(args, "<>|");
		else
			return (parse_error("'|', '>' or '<'' expected"));
		skip_blank(&args->stream);
	}
	return (error);
}
