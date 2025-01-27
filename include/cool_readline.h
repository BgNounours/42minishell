/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cool_readline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:41:32 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/25 15:42:54 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COOL_READLINE_H
# define COOL_READLINE_H

// Same than readline, but do not echo control characters like '^C'
char	*cool_readline(const char *prompt);

#endif
