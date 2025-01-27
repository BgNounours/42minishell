/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ask_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:03:23 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/18 13:40:33 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

const char	*ask_command(t_env *env)
{
	const char	*txt;
	const char	*r;

	txt = cool_readline("\e[1m\e[38;5;45m( ^.^)> \e[0m");
	if (!txt)
		return (NULL);
	r = str_dup(fatal_error, env->mc_command, txt);
	free((char *)txt);
	return (r);
}
