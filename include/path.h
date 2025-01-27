/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:15:12 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/21 16:24:15 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include "include.h"

///// PATH /////

// Search the program in $PATH.
// Returns the path of the program to use, or NULL if there is none.
// If there is several possibilities, it returns the one from the first path
// given in $PATH.
const char	*search_path(
				const t_memclass mc, t_list *variables, const char *prog);

#endif
