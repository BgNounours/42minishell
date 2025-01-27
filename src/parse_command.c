/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:47:40 by mcolonna          #+#    #+#             */
/*   Updated: 2024/07/04 13:49:57 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "parse_command_utils.h"
#include "parse_command_read_string.h"
#include "parse_command_read_element.h"

// Ask the user for data and set readfd to the fd which will receive this
// data.
// Returns 'errno' on error.
static int	heredoc(t_memclass mc, int *readfd, const char *eof)
{
	const t_memclass		mc_in = mem_subclass(fatal_error, mc);
	int						outpipe[2];
	char					*line;
	const t_const_string	eof_line = str_join(fatal_error, mc_in, eof, "\n");

	if (pipe(outpipe) == -1)
		return (minishell_error("errno"), errno);
	*readfd = outpipe[0];
	while (true)
	{
		line = cool_readline("\e[38;5;33m( 'o')> \e[0m");
		if (!line)
			continue ;
		if (str_eq(line, eof) || str_eq(line, eof_line))
			break ;
		print_str(err_remember, outpipe[1], line);
		print_str(err_remember, outpipe[1], "\n");
		free(line);
		if (err_get())
			return (minishell_error("errno"), errno);
	}
	mem_freeall(mc_in);
	if (close(outpipe[1]) == -1)
		return (minishell_error("errno"), errno);
	return (0);
}

// Check if the command is a variable definition.
// If possible, change 'variables' accordingly and return true. 
// If not, return false.
static bool	parse_variable_set_command(
				t_parsing_args *args, const char *command, t_list *variables)
{
	const char	*name;
	const char	*value;

	streamstr_init(&args->stream, command);
	skip_blank(&args->stream);
	name = str_dup(fatal_error, args->mc, "");
	read_only(args, &name, SYMBOL_CHARS);
	if (str_len(name) == 0 || stream_pop(&args->stream) != '=')
		return (false);
	value = read_string(args, "<>|");
	if (args->r.error)
		return (false);
	if (!value)
		value = "";
	skip_blank(&args->stream);
	if (stream_read(&args->stream))
		return (false);
	variables_set(variables, name, value);
	return (true);
}

// Read the command from the stream, and define args and args->r accordingly.
static void	read_command(t_parsing_args *args)
{
	while (!args->r.error && stream_read(&args->stream))
	{
		args->r.error = read_element(args);
		skip_blank(&args->stream);
	}
	if (!args->r.error)
		args->r.calls = (t_call *)list_convert_type(
				fatal_error, args->mc, &args->calls, sizeof(t_call));
}

// Create a t_parsing_args shared between all the parse_command subfunctions.
// Define every fields but .stream
static t_parsing_args	init_parsing_args(t_env *env, const t_memclass mc,
							t_list *variables)
{
	const t_parsing_args	r = {
		.r = {
		.error = 0,
		.empty = false,
		.input_fd = 0,
		.output_fd = 1,
	},
		.mc = mc,
		.calls = list_createempty(mc),
		.got_first_call = false,
		.heredoc = NULL,
		.variables = variables,
		.env = env,
	};

	return (r);
}

// - If the command string contains call(s), return the t_command to execute.
//   - If necessary, input the user for the heredoc.
// - If the command string is a variable definition, define it and return
//   an "empty" t_command.
// - If the command string is empty (or blank), return an "empty" t_command.
// - If there is any error, return a t_command with .error != 0.
t_command	parse_command(t_env *env, const char *command)
{
	t_parsing_args	args;

	args = init_parsing_args(env, env->mc_command, env->variables);
	if (parse_variable_set_command(&args, command, env->variables))
	{
		args.r.empty = true;
		return (args.r);
	}
	streamstr_init(&args.stream, command);
	skip_blank(&args.stream);
	if (!stream_read(&args.stream))
	{
		args.r.empty = true;
		return (args.r);
	}
	read_command(&args);
	if (!args.r.error && args.heredoc)
		args.r.error = heredoc(env->mc_command, &args.r.input_fd, args.heredoc);
	return (args.r);
}
