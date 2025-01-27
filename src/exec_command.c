/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:48:00 by jschaft           #+#    #+#             */
/*   Updated: 2024/07/01 14:32:09 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "exec_command_utils.h"

static void	close_all_pipes(t_exec_command_global *global)
{
	int	i;

	i = 0;
	if (global->pipes[i].pipe[0] != 0)
		if (close(global->pipes[i].pipe[0]) < 0)
			minishell_error("errno");
	while (++i < global->nb_calls)
	{
		if (close(global->pipes[i].pipe[0]) < 0)
			minishell_error("errno");
		if (close(global->pipes[i].pipe[1]) < 0)
			minishell_error("errno");
	}
	if (global->pipes[i].pipe[1] != 1)
		if (close(global->pipes[i].pipe[1]) < 0)
			minishell_error("errno");
}

// Execute a program with specific stdin and stdout:
// - inout[0] is stdin
// - inout[1] is stdout
// If call.program doesn't have any '/' in it, find the program in $PATH.
// If the program wasn't to found in $PATH, or the fork didn't work,
// write the error and return the error status.
static int	execute_call(
				t_exec_command_global *global, t_call call,
				const int inout[2], char *const envp[])
{
	pid_t		pid;
	const char	*program_path;

	program_path = search_path(global->mc, global->env->variables,
			call.program);
	if (!program_path && !is_builtin(call.program))
		return (minishell_error(str_join(fatal_error, global->mc,
					"command not found: ", call.program)), 127);
	if (is_builtin(call.program))
		return (exec_builtin(global->env, call, (int *)inout));
	pid = fork();
	if (pid < 0)
		return (minishell_error("errno"), errno);
	if (pid == 0)
	{
		handle_signals(SIGMODE_DEFAULT);
		if (dup2(inout[0], 0) < 0 || dup2(inout[1], 1) < 0)
			return (minishell_error("errno"), errno);
		close_all_pipes(global);
		execve(program_path, call.argv, envp);
		return (minishell_error("errno"), errno);
	}
	return (0);
}

static int	create_pipes(t_exec_command_global *global, t_command command)
{
	int	i;

	global->pipes = mem_alloc(
			err_remember, global->mc, sizeof(t_pipes) * (global->nb_calls + 1));
	if (err_get())
		return (minishell_error("errno"), errno);
	i = 0;
	global->pipes[i].pipe[0] = command.input_fd;
	while (++i < global->nb_calls)
		if (pipe(global->pipes[i].pipe) < 0)
			return (minishell_error("errno"), errno);
	global->pipes[i].pipe[1] = command.output_fd;
	return (0);
}

static int	exec_each_call(t_exec_command_global *global,
				t_command command, t_env *env)
{
	int			i;
	int			r;
	int			inout[2];
	t_memclass	mc;

	i = -1;
	while (++i < global->nb_calls)
	{
		mc = mem_subclass(fatal_error, global->mc);
		inout[0] = global->pipes[i].pipe[0];
		inout[1] = global->pipes[i + 1].pipe[1];
		r = execute_call(global, command.calls[i], inout,
				variables_envp(env->variables, mc));
		mem_freeall(mc);
		if (r)
			return (r);
	}
	return (r);
}

int	execute_command(t_env *env, t_command command)
{
	t_exec_command_global	global;
	int						r;
	int						wstatus;

	wstatus = 0;
	r = 0;
	global.mc = env->mc_command;
	global.nb_calls = 0;
	global.env = env;
	while (command.calls[global.nb_calls].program != NULL)
		global.nb_calls++;
	if (global.nb_calls == 0)
		return (minishell_error("no program given"), 1);
	r = create_pipes(&global, command);
	if (r)
		return (r);
	r = exec_each_call(&global, command, env);
	close_all_pipes(&global);
	while (wait(&wstatus) != -1)
		;
	if (errno != ECHILD)
		return (minishell_error("errno"), errno);
	if (WEXITSTATUS(wstatus))
		r = WEXITSTATUS(wstatus);
	return (r);
}
