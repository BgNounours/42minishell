/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:11:25 by mcolonna          #+#    #+#             */
/*   Updated: 2024/02/12 13:27:20 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STREAM_H
# define STREAM_H

// Represents a stream.
// Allows to read a string char by char and remembering the position.
typedef struct s_stream_2
{
	const char	*str;
	int			i;
}				t_stream_2;

// Return a new malloced t_stream_2 pointer, or NULL if malloc error.
t_stream_2	*stream_2_new(const char *str);
// Get the current char of the stream, '\0' if the string is finished.
char		stream_2_getchar(t_stream_2 *stream);
// Goes to the next char (never after a '\0').
// Returns 1 if it isn't the end, or else 0.
int			stream_2_next(t_stream_2 *stream);
// Returns 1 if it isn't the end, or else 0.
int			stream_2_continues(t_stream_2 *stream);
// Skip 'n' chars.
void		stream_2_skip(t_stream_2 *stream, int n);
// Return a pointer to the current char.
char		*stream_2_pointer(t_stream_2 *stream);

#endif
