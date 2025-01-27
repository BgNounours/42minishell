/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:36:25 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/13 17:02:25 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"

t_list	list_createempty(t_memclass mc)
{
	t_list	r;

	r.first = NULL;
	r.last = NULL;
	r.size = 0;
	r.mc = mc;
	return (r);
}

void	list_add(t_err *err, t_list *list, void *value)
{
	t_list_element	*new_element;

	new_element = mem_alloc(err, list->mc, sizeof(t_list_element));
	if (!new_element)
		return ;
	new_element->value = value;
	new_element->next = NULL;
	new_element->previous = list->last;
	if (list->last)
	{
		list->last->next = new_element;
		list->last = new_element;
	}
	else
	{
		list->first = new_element;
		list->last = new_element;
	}
	list->size++;
}

void	list_revadd(t_err *err, t_list *list, void *value)
{
	t_list_element	*new_element;

	new_element = mem_alloc(err, list->mc, sizeof(t_list_element));
	if (!new_element)
		return ;
	new_element->value = value;
	new_element->next = list->first;
	new_element->previous = NULL;
	if (list->first)
	{
		list->first->previous = new_element;
		list->first = new_element;
	}
	else
	{
		list->first = new_element;
		list->last = new_element;
	}
	list->size++;
}

void	*list_get(t_err *err, const t_list *list, int index)
{
	t_list_element	*el;

	el = list->first;
	if (index < 0)
		return ((*err)("index error"), NULL);
	while (el && index)
	{
		el = el->next;
		index--;
	}
	if (!el)
		return ((*err)("index error"), NULL);
	return (el->value);
}

void	*list_revget(t_err *err, t_list list, int index)
{
	t_list_element	*el;

	el = list.last;
	while (el && index)
	{
		el = el->previous;
		index--;
	}
	if (!el)
		return ((*err)("index error"), NULL);
	return (el->value);
}
