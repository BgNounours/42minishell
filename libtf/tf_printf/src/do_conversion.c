/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:14:36 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/12 13:30:36 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "do_conversion.h"
#include "conversions.h"

int	do_conversion(va_list args, char name)
{
	static const t_conversion	conversions[] = {
	{'c', &put_char},
	{'s', &put_str},
	{'%', &put_percent},
	{'d', &put_decimal},
	{'i', &put_decimal},
	{'u', &put_unsigned},
	{'x', &put_hex_lower},
	{'X', &put_hex_upper},
	{'p', &put_pointer},
	{'\0', NULL}
	};
	int							i;

	i = 0;
	while (conversions[i].name)
	{
		if (conversions[i].name == name)
			return (conversions[i].put_function(args));
		i++;
	}
	return (-1);
}
