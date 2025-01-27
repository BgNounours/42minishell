/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print_builtin.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:57:19 by jschaft           #+#    #+#             */
/*   Updated: 2024/07/04 12:19:08 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	export_print_builtin_loop(char *const var, int std[2])
{
	int		i;
	char	c[2];

	c[1] = '\0';
	i = 0;
	print_str(fatal_error, std[1], "declare -x ");
	while (var[i] != '=')
	{
		c[0] = var[i];
		print_str(fatal_error, std[1], c);
		i++;
	}
	print_str(fatal_error, std[1], "=\"");
	i++;
	while (var[i])
	{
		c[0] = var[i];
		print_str(fatal_error, std[1], c);
		i++;
	}
	print_str(fatal_error, std[1], "\"\n");
}

int	export_print_builtin(t_env *env, t_call call, int std[2])
{
	int					i;
	const t_memclass	mc = mem_subclass(fatal_error, env->mc_global);
	char *const			*envp = variables_envp(env->variables, mc);

	(void)call;
	i = 0;
	while (envp[i])
	{
		export_print_builtin_loop(envp[i], std);
		i++;
	}
	return (0);
}
