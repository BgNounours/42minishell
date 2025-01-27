/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:45:39 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/12 13:31:08 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERSIONS_H
# define CONVERSIONS_H

# include <stdlib.h>
# include <stdarg.h>

// Does a specific conversion.
// - flags: the flags of the conversion
// - args: the args given to ft_printf
// Return the number of chars written.
// ERROR: returns -1.
typedef int	(t_put_function)(va_list args);

// Represents a possible conversion.
// Ex: {'c', &put_char} is the conversion to write a char.
// .name:			Code to identify the conversion
// 					'c' would mean you have to use it with "%c"
// .put_function:	Function called with the argument to write the data.
// 					-	flags: The flags to modify the way the content is wrote.
// 					-	content: The arguments of printf.
// 					Returned value: The number of chars wrote, -1 if error.
typedef struct s_conversion
{
	char			name;
	t_put_function	*put_function;
}					t_conversion;

// 'c' conversion.
int	put_char(va_list args);
// 's' conversion.
int	put_str(va_list args);
// '%' conversion.
int	put_percent(va_list args);
// 'd' and 'i' conversions (it's the same).
int	put_decimal(va_list args);
// 'u' conversion.
int	put_unsigned(va_list args);
// 'x' conversion.
int	put_hex_lower(va_list args);
// 'X' conversion.
int	put_hex_upper(va_list args);
// 'p' conversion.
int	put_pointer(va_list args);

#endif
