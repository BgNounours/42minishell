/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:31:39 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/12 12:57:29 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "stream.h"

char			*ft_strjoin(char const *s1, char const *s2);

// Cast an int to a string (0 or /[1-9][0-9]*/).
// - n: number
char			*ft_itoa(int n);

// Cast an unsigned int to a string (0 or /-?[1-9][0-9]*/).
// - n: number
char			*ft_utoa(unsigned int n);

// Cast an unsigned int to a string in a specified base.
// - n: number
// - base: base chars (example: "01233456789abcdef")
char			*ft_utoa_base(unsigned long n, const char *base);

// atoi for a stream.
unsigned int	stream_atoi(t_stream_2 *stream);

#endif
