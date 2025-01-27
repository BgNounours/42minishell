/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_read_element.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:47:40 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/27 15:02:36 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_COMMAND_READ_ELEMENT_H
# define PARSE_COMMAND_READ_ELEMENT_H

# include "include.h"
# include "parse_command_utils.h"

// Read an element from the stream (a call to a program or a redirection)
// Change args accordingly.
// On success, return 0. On error, return the error status.
int	read_element(t_parsing_args *args);

#endif
