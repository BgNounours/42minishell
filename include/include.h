/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:15:12 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/27 13:48:28 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <stdbool.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <strings.h>
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <termios.h>
# include "libft.h"
# include "libtf.h"

# include "main.h"
# include "variables.h"
# include "cool_readline.h"
# include "ask_command.h"
# include "parse_command.h"
# include "exec_command.h"
# include "error.h"
# include "path.h"
# include "builtins.h"
# include "signalhandler.h"

#endif
