/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:38:27 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/20 17:07:33 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libtf.h"
#include <unistd.h>

void	print_str(t_err *err, int fd, t_const_string str)
{
	if (write(fd, str, str_len(str)) == -1)
		(*err)("errno");
}

void	print_line(t_err *err, int fd, t_const_string str)
{
	print_str(err, fd, str);
	if (write(fd, "\n", 1) == -1)
		(*err)("errno");
}
