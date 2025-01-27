/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:05:28 by mcolonna          #+#    #+#             */
/*   Updated: 2024/04/25 16:19:00 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"

void	**list_convert(t_err *err, t_memclass mc, const t_list *list)
{
	const int	size = list_getsize(list);
	int			i;
	void		**r;

	r = mem_alloc(err, mc, (size + 1) * sizeof(void *));
	i = -1;
	while (++i < size)
		r[i] = list_get(err, list, i);
	r[i] = NULL;
	return (r);
}

static void	fill_with_0(char *dest, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		dest[i] = '\0';
}

void	*list_convert_type(t_err *err,
			t_memclass mc, const t_list *list, int size)
{
	const t_memclass	mc_in = mem_subclass(err, mc);
	char **const		list2 = (char **)list_convert(err, mc_in, list);
	const int			listsize = list_getsize(list);
	char				*r;
	int					i;

	r = mem_alloc(err, mc, (listsize + 1) * size);
	i = -1;
	while (++i < listsize)
		data_cpy(r + i * size, list2[i], size);
	fill_with_0(r + i * size, size);
	return (r);
}
