/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:47:40 by mcolonna          #+#    #+#             */
/*   Updated: 2024/07/01 13:38:03 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "variables_utils.h"

void	variables_set(t_list *variables, const char *name, const char *value)
{
	t_variable	*var;

	var = variables_find(variables, name);
	var->value = str_dup(fatal_error, variables->mc, value);
}

const char	*variables_get(t_list *variables, const char *name)
{
	return (variables_find(variables, name)->value);
}

void	variables_export(t_list *variables, const char *name)
{
	variables_find(variables, name)->exported = true;
}

void	variables_unset(t_list *variables, const char *name)
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
		{
			if (el->previous)
				el->previous->next = el->next;
			else
				variables->first = el->next;
			if (el->next)
				el->next->previous = el->previous;
			else
				variables->last = el->previous;
			variables->size--;
			mem_free(el->value);
			mem_free(el);
		}
		el = next;
	}
}

char *const	*variables_envp(t_list *variables, t_memclass mc)
{
	t_list_element	*el;
	const int		count = variables_countexported(variables);
	char			**r;
	int				i;
	char			*tmp;

	r = mem_alloc(fatal_error, mc, (count + 1) * sizeof(char *));
	el = variables->first;
	i = -1;
	while (el)
	{
		if (((t_variable *)(el->value))->exported)
		{
			tmp = str_join(
					fatal_error, mc, ((t_variable *)(el->value))->name, "=");
			r[++i] = str_join(
					fatal_error, mc, tmp, ((t_variable *)(el->value))->value);
			mem_free(tmp);
		}
		el = el->next;
	}
	r[++i] = NULL;
	return (r);
}
