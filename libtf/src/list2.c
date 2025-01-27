/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:58:05 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/13 17:02:42 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"

void	*list_pop(t_err *err, t_list *list)
{
	t_list_element	*r;
	void			*rr;

	if (!list->first)
		return ((*err)("empty list"), NULL);
	r = list->first;
	list->first = r->next;
	if (!list->first)
		list->last = NULL;
	else
		list->first->previous = NULL;
	list->size--;
	rr = r->value;
	mem_free(r);
	return (rr);
}

void	*list_revpop(t_err *err, t_list *list)
{
	t_list_element	*r;
	void			*rr;

	if (!list->last)
		return ((*err)("empty list"), NULL);
	r = list->last;
	list->last = r->previous;
	if (!list->last)
		list->first = NULL;
	else
		list->first->next = NULL;
	list->size--;
	rr = r->value;
	mem_free(r);
	return (rr);
}

int	list_getsize(const t_list *list)
{
	return (list->size);
}

void	list_rotate(t_list *list)
{
	t_list_element	*el;

	if (list->size == 0)
		return ;
	el = list->first;
	list->first = el->next;
	list->last->next = el;
	el->previous = list->last;
	el->next->previous = NULL;
	el->next = NULL;
	list->last = el;
}

void	list_revrotate(t_list *list)
{
	t_list_element	*el;

	if (list->size == 0)
		return ;
	el = list->last;
	list->last = el->previous;
	list->first->previous = el;
	el->next = list->first;
	el->previous->next = NULL;
	el->previous = NULL;
	list->first = el;
}
