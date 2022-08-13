/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:52:39 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/13 17:54:22 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	no_env(void)
{
	// if we unset PATH, we will print this error like bash
	if (!g_data.env)
	{
        g_data.exit_status = 127;
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(((t_cmd *)(g_data.cmds->content))->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
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
	if (((t_cmd *)(g_data.cmds->content))->args[1] == NULL)
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
		g_data.exit_status = 127;
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(((t_cmd *)(g_data.cmds->content))->args[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}
