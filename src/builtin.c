/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:02:45 by jschaft           #+#    #+#             */
/*   Updated: 2024/07/04 11:56:59 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static int	unset_builtin(t_env *env, t_call call, int std[2])
{
	int			i;

	(void)std;
	i = 0;
	while (call.argv[++i])
		variables_unset(env->variables, call.argv[i]);
	return (0);
}

// Check if str is the name of a builtin.
// Return true if it is, false if not.
bool	is_builtin(const char *str)
{
	return (
		ft_strncmp(str, "cd", 3) == 0
		|| ft_strncmp(str, "exit", 5) == 0
		|| ft_strncmp(str, "export", 7) == 0
		|| ft_strncmp(str, "env", 4) == 0
		|| ft_strncmp(str, "pwd", 4) == 0
		|| ft_strncmp(str, "echo", 5) == 0
		|| ft_strncmp(str, "unset", 6) == 0
	);
}

// Execute the builtin pwd for the current directory.
// Return 0 for the sake of returning something for exec_builtin
static int	pwd_builtin(t_env *env, t_call call, int std[2])
{
	char	*str;

	(void)env;
	(void)call;
	str = getcwd(NULL, 0);
	print_line(fatal_error, std[1], str);
	free(str);
	return (0);
}

static int	env_builtin(t_env *env, t_call call, int std[2])
{
	int					i;
	const t_memclass	mc = mem_subclass(fatal_error, env->mc_global);
	char *const			*envp = variables_envp(env->variables, mc);

	if (call.argv[1])
	{
		print_line(fatal_error, 2, "too many arguments");
		return (1);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		print_line(fatal_error, std[1], envp[i]);
		i++;
	}
	mem_freeall(mc);
	return (0);
}

// Execute the specified builtin.
// The builtin must exist.
// Return the error value returned by the builtin.
int	exec_builtin(t_env *env, t_call call, int std[2])
{
	if (ft_strncmp(call.program, "cd", 3) == 0)
		return (cd_builtin(env, call, std));
	if (ft_strncmp(call.program, "exit", 5) == 0)
		return (exit_builtin(env, call, std));
	if (ft_strncmp(call.program, "export", 7) == 0 && call.argc != 1)
		return (export_builtin(env, call, std));
	if (ft_strncmp(call.program, "export", 7) == 0 && call.argc == 1)
		return (export_print_builtin(env, call, std));
	if (ft_strncmp(call.program, "unset", 6) == 0)
		return (unset_builtin(env, call, std));
	if (ft_strncmp(call.program, "pwd", 4) == 0)
		return (pwd_builtin(env, call, std));
	if (ft_strncmp(call.program, "echo", 5) == 0)
		return (echo_builtin(env, call, std));
	if (ft_strncmp(call.program, "env", 4) == 0)
		return (env_builtin(env, call, std));
	return (1);
}
