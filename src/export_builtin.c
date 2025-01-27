/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:28:29 by jschaft           #+#    #+#             */
/*   Updated: 2024/07/03 12:17:03 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static bool	export_builtin_2(t_env *env, t_memclass mc, char **name,
	const char *arg)
{
	int	i;

	i = -1;
	while (arg[++i] != '=')
		;
	*name = mem_alloc(fatal_error, mc, (i + 1) * sizeof(char));
	i = -1;
	while (arg[++i] != '=')
		(*name)[i] = arg[i];
	(*name)[i] = '\0';
	if (!variables_nameisvalid(*name))
		return (false);
	variables_set(env->variables, *name, arg + i + 1);
	return (true);
}

int	export_builtin(t_env *env, t_call call, int std[2])
{
	int					i;
	char				*name;
	const t_memclass	mc = mem_subclass(fatal_error, env->mc_global);
	int					r;

	(void)std;
	r = 0;
	i = 0;
	while (call.argv[++i])
	{
		if (char_isin('=', call.argv[i]) && export_builtin_2(
				env, mc, &name, call.argv[i]));
		else if (variables_nameisvalid(call.argv[i]))
			name = call.argv[i];
		else
		{
			print_line(fatal_error, 2, "builtin: bad variable name");
			r = 1;
			continue ;
		}
		variables_export(env->variables, name);
	}
	mem_freeall(mc);
	return (r);
}
