/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:15:12 by mcolonna          #+#    #+#             */
/*   Updated: 2024/07/04 12:02:43 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "include.h"

// for the 'std' parameter in all these functions:
// - std[0] is stdin
// - std[1] is stdout

// Check if the command is a builtin.
bool		is_builtin(const char *str);

// Execute the builtin command
int			exec_builtin(t_env *env, t_call call, int std[2]);

// Execute echo builtin
int			echo_builtin(t_env *env, t_call call, int std[2]);

// Execute cd builtin
int			cd_builtin(t_env *env, t_call call, int std[2]);

// Execute export builtin with no arguments
int			export_print_builtin(t_env *env, t_call call, int std[2]);

// Execute export builtin
int			export_builtin(t_env *env, t_call call, int std[2]);

// Execute exit builtin
int			exit_builtin(t_env *env, t_call call, int std[2]);

#endif
