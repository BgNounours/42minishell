/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 13:43:21 by mcolonna          #+#    #+#             */
/*   Updated: 2024/07/03 14:09:27 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLES_H
# define VARIABLES_H

# define SYMBOL_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz\
_0123456789"

typedef struct s_variable
{
	const char	*name;
	const char	*value;
	bool		exported;
}	t_variable;

// Set a variable to a new value.
void		variables_set(t_list *variables, const char *name,
				const char *value);

// Get the value of a variable from its name.
const char	*variables_get(t_list *variables, const char *name);

// Set a variable as exported.
void		variables_export(t_list *variables, const char *name);

// Unset a variable.
void		variables_unset(t_list *variables, const char *name);

// Get a envp of all exported variables.
char *const	*variables_envp(t_list *variables, t_memclass mc);

// Return true if 'name' is a valid variable name.
bool		variables_nameisvalid(const char *name);

#endif
