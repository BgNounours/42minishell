/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:28:29 by jschaft           #+#    #+#             */
/*   Updated: 2024/07/04 13:35:21 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	exit_builtin(t_env *env, t_call call, int std[2])
{
	int	r;

	(void)std;
	if (call.argv[1] && call.argv[2])
	{
		print_line(fatal_error, 2, "exit: too many arguments");
		return (1);
	}
	r = env->errorstatus;
	if (call.argv[1])
	{
		r = (int)str_touint(err_remember, call.argv[1]);
		if (err_get())
		{
			print_line(fatal_error, 2, "exit: numeric argument required");
			return (1);
		}
	}
	env->exit = true;
	return (r);
}

int	echo_builtin(t_env *env, t_call call, int std[2])
{
	int		i;
	bool	newline;

	(void)env;
	i = 1;
	newline = true;
	if (call.argv[1] && str_eq(call.argv[1], "-n"))
	{
		newline = false;
		i++;
	}
	while (call.argv[i] != NULL)
	{
		print_str(fatal_error, std[1], call.argv[i]);
		if (call.argv[i + 1] != NULL)
			print_str(fatal_error, std[1], " ");
		i++;
	}
	if (newline)
		print_str(fatal_error, std[1], "\n");
	return (0);
}

static const char	*go_home(t_env *env, bool to_old)
{
	if (!to_old)
		return (variables_get(env->variables, "HOME"));
	else
		return (variables_get(env->variables, "OLDPWD"));
}

// Execute the builtin cd for the specified path.
// Return 0 if success, errno if error.
int	cd_builtin(t_env *env, t_call call, int std[2])
{
	int			r;
	const char	*pwd;
	const bool	go_oldpwd = call.argv[1] && str_eq(call.argv[1], "-");

	(void)std;
	if (call.argc == 1 || go_oldpwd)
		pwd = go_home(env, go_oldpwd);
	else if (call.argc == 2)
		pwd = call.argv[1];
	else
		return (print_line(fatal_error, 2, "cd: too many arguments"), 1);
	r = chdir(pwd);
	if (r)
		return (perror("cd"), errno);
	mem_free((char *)variables_get(env->variables, "OLDPWD"));
	variables_set(env->variables, "OLDPWD", "");
	variables_set(env->variables, "OLDPWD",
		variables_get(env->variables, "PWD"));
	pwd = getcwd(NULL, 0);
	variables_set(env->variables, "PWD",
		str_dup(fatal_error, env->mc_global, pwd));
	if (go_oldpwd)
		print_line(fatal_error, 1, pwd);
	free((char *)pwd);
	return (0);
}
