/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:52:39 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/08 15:47:00 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	no_env(void)
{
	// if we unset PATH, we will print this error like bash
	if (!g_data.env)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(g_data.cmd->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 1);
        // exit_code(127);
		return (1);
	}
	return (0);
}

void	ft_env(void)
{
	int	i;

	i = 0;
	if (no_env() == 1)
		return ;
	if (g_data.cmd->args[1] == NULL)
	{
		while (g_data.env[i] != NULL)
		{
			printf("%s\n", g_data.env[i]);
			i++;
		}
		return ;
	}
	else
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(g_data.cmd->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		// exit(127);
	}
}
