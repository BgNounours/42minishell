/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:15:12 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/25 11:46:04 by jschaft          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "include.h"

t_memclass	*get_global_mc_pointer(void);

// Set the global mc freed when exit.
void		set_global_mc(t_memclass mc);

// Call to show an error.
// If msg == "errno", use perror()
void		minishell_error(const char *msg);

// Show the errno error and exit the program.
void		fatal_error(const char *msg);

// Show a specific message and exit the program.
void		fatal_error_msg(const char *msg);

#endif
