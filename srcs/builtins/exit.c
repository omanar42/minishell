/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:10:33 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/29 22:56:08 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	is_numeric(void)
{
	t_cmd	*cmd;
	int		i;
	int		j;

	i = 1;
	j = 0;
	cmd = (t_cmd *)g_data.cmds->content;
	while (cmd->args[i] != NULL)
	{
		while (cmd->args[1][j])
		{
			if (cmd->args[1][j] != '0' && !ft_atoi(&cmd->args[1][j]))
			{
				ft_putstr_fd("exit: ", 2);
				ft_putstr_fd(cmd->args[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				g_data.exit_status = 225;
				exit(g_data.exit_status);
			}
			j++;
		}
		i++;
	}
}

void	exit_cmd(void)
{
	int		len;
	t_cmd	*cmd;

	cmd = (t_cmd *)g_data.cmds->content;
	len = argslen(cmd->args);
	if (cmd->args[1] == NULL)
	{
		if (g_data.signalchild != 1)
			ft_putstr_fd("exit\n", 2);
		exit(g_data.exit_status);
	}
	is_numeric();
	if (len > 3)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_data.exit_status = 1;
	}
	else if (len == 3)
	{
		ft_putstr_fd("exit\n", 1);
		exit(ft_atoi(cmd->args[1]));
	}
}
