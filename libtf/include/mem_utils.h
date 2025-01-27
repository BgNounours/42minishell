/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:37:23 by mcolonna          #+#    #+#             */
/*   Updated: 2024/03/12 16:06:59 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_UTILS_H
# define MEM_UTILS_H

# include "libtf.h"
# include <stdlib.h>

typedef struct s_memclass_in	t_memclass_in;
typedef struct s_element		t_element;

typedef struct s_element
{
	void			*address;
	t_memclass_in	*subclass;
	t_element		*previous;
	t_element		*next;
	t_memclass_in	*mc;
}						t_element;

typedef struct s_memclass_in
{
	t_element	*first;
	t_element	*parent_element;
}				t_memclass_in;

void		*create_address_with_element(t_element *element, size_t size);

t_element	*get_address_element(void *address);

void		free_address_with_element(void *address);

void		freeelement(t_element *el);

#endif
