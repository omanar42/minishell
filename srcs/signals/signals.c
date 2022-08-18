/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 00:46:24 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/18 14:16:22 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handlear(int signal)
{
	if (signal == SIGINT)
	{
		if (g_data.signalchild == 1)
		{
			ft_putstr_fd("^C\n", 1);
			g_data.signalchild = 0;
			g_data.exit_status = 130;
		}
		else
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (signal == SIGQUIT)
	{
		g_data.signalqiut = 0;
		g_data.exit_status = 131;
	}
}

void	init_signal(void)
{
	signal(SIGINT, handlear);
	signal(SIGQUIT, SIG_IGN);
}