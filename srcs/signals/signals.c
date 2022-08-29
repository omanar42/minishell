/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 00:46:24 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/29 17:11:22 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handlear(int signal)
{
	(void)signal;
	if (g_data.signal_heredoc == 0)
	{
		if (g_data.signalchild != 1)
		{
			g_data.exit_status = 1;
			if (g_data.breaker == 0)
				ft_putstr_fd("\n", 2);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			g_data.signalchild = 0;
			ft_putstr_fd("\n", 2);
		}
	}
	else
	{
		g_data.breaker = 1;
		ft_putstr_fd("\n", 2);
		close(0);
	}
}

void	init_signal(void)
{
	signal(SIGINT, handlear);
	signal(SIGQUIT, SIG_IGN);
}
