/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:47:40 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/28 14:35:55 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_UTILS_H
# define VARIABLES_UTILS_H

# include "include.h"

// Return a pointer to the variable 'name'.
// (An undefined variable is considered of an empty value)
t_variable	*variables_find(t_list *variables, const char *name);

// Return the number of exported variables.
int			variables_countexported(t_list *variables);

#endif
