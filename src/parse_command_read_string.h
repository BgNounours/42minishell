/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_read_string.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:47:40 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/27 14:46:02 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_COMMAND_READ_STRING_H
# define PARSE_COMMAND_READ_STRING_H

# include "include.h"
# include "parse_command_utils.h"

// Read the string, stop if the char is in stop_charset.
// Possible syntaxes:
// - /[^(stop_charset)]+/
// - /'.*'/
// - /".*"/
// Change args->r.error and return NULL if error.
const char	*read_string(t_parsing_args *args, const char *stop_charset);

#endif
