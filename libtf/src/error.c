/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 18:47:37 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/06 19:08:01 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"

static t_const_string	pop_msg(t_const_string msg)
{
	static t_const_string	value = NULL;
	t_const_string			tmp;

	tmp = value;
	value = msg;
	return (tmp);
}

void	err_remember(t_const_string msg)
{
	pop_msg(msg);
}

t_const_string	err_get(void)
{
	return (pop_msg(NULL));
}
