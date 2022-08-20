/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 00:46:24 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/20 15:54:26 by adiouane         ###   ########.fr       */
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
		printf("\n");
		g_data.exit_status = 1;
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