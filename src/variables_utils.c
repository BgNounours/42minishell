/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:47:40 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/28 14:30:52 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "variables_utils.h"

t_variable	*variables_find(t_list *variables, const char *name)
{
	t_list_element	*el;
	t_list_element	*next;
	t_variable		*r;

	el = variables->first;
	while (el)
	{
		next = el->next;
		r = (t_variable *)el->value;
		if (str_eq(r->name, name))
			return (r);
		if (str_eq(r->value, "") && !r->exported)
			variables_unset(variables, r->name);
		el = next;
	}
	r = mem_alloc(fatal_error, variables->mc, sizeof(t_variable));
	r->name = str_dup(fatal_error, variables->mc, name);
	r->value = "";
	r->exported = false;
	list_add(fatal_error, variables, r);
	return (r);
}

int	variables_countexported(t_list *variables)
{
	int				r;
	t_list_element	*el;

	r = 0;
	el = variables->first;
	while (el)
	{
		if (((t_variable *)(el->value))->exported)
			r++;
		el = el->next;
	}
	return (r);
}
