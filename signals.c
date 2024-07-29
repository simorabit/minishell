/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 12:51:06 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/29 14:36:16 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_s;

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_s = 1;
		if (waitpid(-1, NULL, WNOHANG) == 0)
		{
			printf("\n");
			return ;
		}
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	notify_signals(void)
{
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
}
