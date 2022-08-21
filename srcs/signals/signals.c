/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 00:46:24 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/21 05:27:26 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handlear(int signal)
{
	if (g_data.signal_heredoc == 1)
	{
		g_data.signal_heredoc = 0;
		return ;
	}
	if (signal == SIGINT)
	{
		if (g_data.signalchild == 1)
		{
			g_data.signalchild = 0;
			printf("\n");
			return ;
		}
		g_data.exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	init_signal(void)
{
	signal(SIGINT, handlear);
	signal(SIGQUIT, SIG_IGN);
}
