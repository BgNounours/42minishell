/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:04:30 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/28 12:52:32 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

static void	handle_sigint(int _)
{
	(void)_;
	print_line(fatal_error, 2, "");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_signals(t_sigmode sigmode)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	if (sigmode == SIGMODE_PROMPT)
		sa.sa_flags = SA_RESTART;
	if (sigmode == SIGMODE_PROMPT)
		sa.sa_handler = handle_sigint;
	else if (sigmode == SIGMODE_IGNORE)
		sa.sa_handler = SIG_IGN;
	else
		sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		fatal_error(NULL);
	sa.sa_flags = 0;
	if (sigmode == SIGMODE_DEFAULT)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		fatal_error(NULL);
}
