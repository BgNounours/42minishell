/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:33:45 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/28 14:10:09 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static t_list	variables_from_envp(t_env env, char *const envp[])
{
	t_list		r;
	char		**splitted;
	t_variable	*var;
	int			i;

	r = list_createempty(env.mc_global);
	i = -1;
	while (envp[++i])
	{
		splitted = str_split(fatal_error, env.mc_global, envp[i], "=");
		if (!splitted[0] || ! splitted[1])
			continue ;
		var = mem_alloc(fatal_error, env.mc_global, sizeof(t_variable));
		var->name = splitted[0];
		var->value = splitted[1];
		var->exported = true;
		list_add(fatal_error, &r, var);
	}
	return (r);
}

// Execute a command from a string.
static int	do_command(t_env *env, const char *str)
{
	t_command			command;
	int					r;

	command = parse_command(env, str);
	if (command.error || command.empty)
		return (command.error);
	r = execute_command(env, command);
	return (r);
}

static void	start(t_env *env)
{
	env->mc_command = mem_subclass(fatal_error, env->mc_global);
	do_command(env, "clear");
	do_command(env, "cat ./header");
	do_command(env, "echo");
	mem_freeall(env->mc_command);
	env->mc_command = NULL;
}

static void	prompt_command(t_env *env)
{
	const char		*command_str;

	env->mc_command = mem_subclass(fatal_error, env->mc_global);
	handle_signals(SIGMODE_PROMPT);
	command_str = ask_command(env);
	handle_signals(SIGMODE_IGNORE);
	if (!command_str)
		env->exit = true;
	else
	{
		add_history(command_str);
		env->errorstatus = do_command(env, command_str);
	}
	mem_freeall(env->mc_command);
	env->mc_command = NULL;
}

int	main(const int argc, const char *argv[], char *const envp[])
{
	t_env			env;
	t_list			variables;

	(void)argv;
	if (argc != 1)
	{
		minishell_error("Takes no argument");
		return (2);
	}
	env.exit = false;
	env.mc_global = mem_newclass(fatal_error);
	set_global_mc(env.mc_global);
	env.mc_command = NULL;
	env.errorstatus = 0;
	variables = variables_from_envp(env, envp);
	env.variables = &variables;
	start(&env);
	while (!env.exit)
		prompt_command(&env);
	mem_freeall(env.mc_global);
	return (env.errorstatus);
}
