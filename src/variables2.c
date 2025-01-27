/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:39:55 by mcolonna          #+#    #+#             */
/*   Updated: 2024/07/02 15:41:42 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

bool	variables_nameisvalid(const char *name)
{
	int	i;

	i = -1;
	while (name[++i])
		if (!char_isin(name[i], SYMBOL_CHARS))
			return (false);
	return (true);
}
