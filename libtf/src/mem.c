/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:08:16 by mcolonna          #+#    #+#             */
/*   Updated: 2024/04/29 13:47:37 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"
#include "mem_utils.h"
#include <stdlib.h>

t_memclass	mem_newclass(t_err *err)
{
	t_memclass_in	*r;

	r = malloc(sizeof(t_memclass_in));
	if (!r)
		return ((*err)("alloc error"), NULL);
	r->first = NULL;
	r->parent_element = NULL;
	return (r);
}

void	*mem_alloc(t_err *err, t_memclass mc, size_t size)
{
	void			*r;
	t_element		*new_element;
	t_memclass_in	*mc_in;

	mc_in = (t_memclass_in *) mc;
	new_element = malloc(sizeof(t_element));
	if (!new_element)
		return ((*err)("alloc error"), NULL);
	r = create_address_with_element(new_element, size);
	if (!r)
		return (free(new_element), (*err)("alloc error"), NULL);
	new_element->address = r;
	new_element->subclass = NULL;
	new_element->next = mc_in->first;
	if (new_element->next)
		new_element->next->previous = new_element;
	new_element->previous = NULL;
	new_element->mc = mc;
	mc_in->first = new_element;
	return (r);
}

void	mem_freeall(t_memclass mc)
{
	t_element	*el;
	t_element	*next;

	if (!mc)
		return ;
	el = ((t_memclass_in *) mc)->first;
	while (el)
	{
		el->previous = NULL;
		next = el->next;
		free_address_with_element(el->address);
		if (el->subclass)
			mem_freeall(el->subclass);
		else
			free(el);
		el = next;
	}
	if (((t_memclass_in *) mc)->parent_element)
		freeelement(((t_memclass_in *) mc)->parent_element);
	free(mc);
}

void	mem_free(void *address)
{
	t_element	*el;

	if (!address)
		return ;
	el = get_address_element(address);
	free_address_with_element(address);
	freeelement(el);
}

t_memclass	mem_subclass(t_err *err, t_memclass parent)
{
	t_memclass_in	*r;
	t_memclass_in	*parent_in;
	t_element		*new_element;

	parent_in = (t_memclass_in *) parent;
	r = mem_newclass(err);
	if (!r)
		return (err("alloc error"), NULL);
	new_element = malloc(sizeof(t_element));
	if (!new_element)
		return (err("alloc error"), mem_freeall(r), NULL);
	new_element->address = NULL;
	new_element->subclass = r;
	new_element->next = parent_in->first;
	if (new_element->next)
		new_element->next->previous = new_element;
	new_element->previous = NULL;
	new_element->mc = parent;
	parent_in->first = new_element;
	r->parent_element = new_element;
	return ((t_memclass) r);
}
