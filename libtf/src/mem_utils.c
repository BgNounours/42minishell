/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:36:49 by mcolonna          #+#    #+#             */
/*   Updated: 2024/03/11 14:03:20 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem_utils.h"

void	freeelement(t_element *el)
{
	if (el->previous)
		el->previous->next = el->next;
	else
		el->mc->first = el->next;
	if (el->next)
		el->next->previous = el->previous;
	free(el);
}

void	*create_address_with_element(t_element *element, size_t size)
{
	void	*r;

	r = malloc(sizeof(t_element *) + size);
	if (!r)
		return (free(r), NULL);
	*((t_element **)r) = element;
	return ((void *)((char *)r + sizeof(t_element *)));
}

t_element	*get_address_element(void *address)
{
	return (*(t_element **)((char *)address - sizeof(t_element *)));
}

void	free_address_with_element(void *address)
{
	if (address)
		free((char *)address - sizeof(t_element *));
}
