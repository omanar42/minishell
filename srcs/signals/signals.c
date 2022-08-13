/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 00:46:24 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/13 10:58:50 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handlear(int signal)
{
	if (signal == SIGINT)
	{
		// if (g_data.signal_child == 1)
		// {
		// 	printf("\n");
		// 	g_data.signal_child = 0;
		// }
		// else
		// {
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		// }
		
	}
	else if (signal == SIGQUIT)
	{
		printf("\n");
		rl_redisplay();
		rl_on_new_line();
		rl_redisplay();
	}
}

void	init_signal(void)
{
	signal(SIGINT, handlear);
	signal(SIGQUIT, handlear);
}