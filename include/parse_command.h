/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:15:12 by mcolonna          #+#    #+#             */
/*   Updated: 2024/07/01 11:16:02 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_COMMAND_H
# define PARSE_COMMAND_H

# include "include.h"

// Represents a call to a program (the program name and its arguments)
typedef struct s_call
{
	const char			*program;
	int					argc;
	char *const			*argv;
}						t_call;

// Represents a command given by the user.
typedef struct s_command
{
	int				error;
	bool			empty;
	const t_call	*calls;
	int				input_fd;
	int				output_fd;
}					t_command;

// An element of a list of pipes
typedef struct s_pipes
{
	int	pipe[2];
}		t_pipes;

// Return the t_command representing the command given by the user.
// If error, return a t_command wth the value .error = true.
t_command	parse_command(t_env *env, const char *command);

const char	*variables_get(t_list *variables, const char *name);

#endif
