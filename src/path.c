/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:07:26 by jschaft           #+#    #+#             */
/*   Updated: 2024/06/28 15:28:55 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static const char	**get_path(const t_memclass mc, t_list *variables)
{
	const char	**re;
	const char	*path;

	path = variables_get(variables, "PATH");
	re = (const char **)str_split(fatal_error, mc, path, ":");
	return (re);
}

static bool	is_path(const char *str)
{
	return (char_isin('/', str));
}

const char	*search_path(
		const t_memclass mc, t_list *variables, const char *prog)
{
	const char	**path = get_path(mc, variables);
	const char	*prog2 = str_join(fatal_error, mc, "/", prog);
	int			i;
	const char	*r;

	if (is_path(prog))
	{
		if (access(prog, X_OK) >= 0)
			return (str_dup(fatal_error, mc, prog));
		return (NULL);
	}
	i = 0;
	while (path[i] != NULL)
	{
		r = str_join(fatal_error, mc, path[i], prog2);
		if (access(r, X_OK) >= 0)
			return (r);
		mem_free((void *)r);
		i++;
	}
	mem_free((void *)prog2);
	mem_free(path);
	return (NULL);
}
