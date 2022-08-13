/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:10:33 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/13 07:13:50 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_cmd(void)
{
    // overlap
	if (g_data.cmd->args[1] == NULL)
		exit(g_data.exit_status); // exit last cmd globle exit status_code
	else if (g_data.cmd->args[1] != NULL && ft_isdigit(g_data.cmd->args[1][0]))
	{
		g_data.exit_status = 1;
		ft_putstr_fd("exit \n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	else if (ft_isdigit(g_data.cmd->args[1][0]))
		exit(ft_atoi(g_data.cmd->args[1]));
	else
	{
		ft_putstr_fd("exit: ", 1);
		ft_putstr_fd(g_data.cmd->args[1], 1);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_data.exit_status = 225;
		exit(g_data.exit_status);
	}
}
