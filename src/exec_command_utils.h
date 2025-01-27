/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:48:00 by jschaft           #+#    #+#             */
/*   Updated: 2024/06/27 14:45:14 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_COMMAND_UTILS_H
# define EXEC_COMMAND_UTILS_H

# include "include.h"

typedef struct s_exec_command_global
{
	t_memclass	mc;
	int			nb_calls;
	t_pipes		*pipes;
	t_env		*env;
}				t_exec_command_global;

#endif
