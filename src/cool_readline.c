/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cool_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcolonna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 13:42:58 by mcolonna          #+#    #+#             */
/*   Updated: 2024/06/18 15:39:39 by mcolonna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*cool_readline(const char *prompt)
{
	char			*r;
	struct termios	tty;
	struct termios	tty_old;

	tcgetattr(0, &tty);
	tty_old = tty;
	tty.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &tty);
	r = readline(prompt);
	tcsetattr(0, TCSANOW, &tty_old);
	return (r);
}
