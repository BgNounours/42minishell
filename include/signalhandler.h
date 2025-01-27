/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalhandler.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschaft <cecile.schaft@orange.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:15:12 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/28 12:58:40 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALHANDLER_H
# define SIGNALHANDLER_H

# include "include.h"

typedef enum e_sigmode
{
	SIGMODE_PROMPT,
	SIGMODE_IGNORE,
	SIGMODE_DEFAULT
}	t_sigmode;

// If sigmode is SIGMODE_PROMPT, ^C redisplays the prompt and ^\ is ignored.
// If sigmode is SIGMODE_IGNORE, ^C and ^\ are ignored.
// If sigmode is SIGMODE_DEFAULT, ^C and ^\ are reset by default.
void				handle_signals(t_sigmode sigmode);

#endif
