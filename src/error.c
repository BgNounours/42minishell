/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:51:56 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/25 11:45:46 by jschaft          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_memclass	*get_global_mc_pointer(void)
{
	static t_memclass	r = NULL;

	return (&r);
}

void	set_global_mc(t_memclass mc)
{
	t_memclass *const	dest = get_global_mc_pointer();

	if (*dest)
		fatal_error_msg("Must call set_global_mc() only once.");
	*dest = mc;
}

void	minishell_error(const char *msg)
{
	if (str_eq(msg, "errno"))
		perror("minishell");
	else
	{
		print_str(err_remember, 2, "minishell: ");
		print_line(err_remember, 2, msg);
		err_get();
	}
}

void	fatal_error(const char *msg)
{
	(void)msg;
	minishell_error("errno");
	mem_freeall(*get_global_mc_pointer());
	exit(errno);
}

void	fatal_error_msg(const char *msg)
{
	minishell_error(msg);
	mem_freeall(*get_global_mc_pointer());
	exit(errno);
}
