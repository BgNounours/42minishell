/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_conversion.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:25:00 by mcolonna          #+#    #+#             */
/*   Updated: 2023/11/20 15:19:10 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DO_CONVERSION_H
# define DO_CONVERSION_H

# include <stdarg.h>

// Do a conversion specified by its name.
// - args: arguments given to ft_printf()
// - name: name of the conversion
// Returns the number of chars written.
// ERROR: returns -1.
int	do_conversion(va_list args, char name);

#endif
