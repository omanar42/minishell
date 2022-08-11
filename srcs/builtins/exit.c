/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:10:33 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/08 15:53:57 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_cmd(void)
{
    // overlap
	if (g_data.cmd->args[1] == NULL)
		exit(0); // exit last cmd globle exit status_code
	else if (g_data.cmd->args[1] != NULL && ft_isdigit(g_data.cmd->args[1][0]))
	{
		ft_putstr_fd("exit \n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
	}
	else if (ft_isdigit(g_data.cmd->args[1][0]))
		exit(ft_atoi(g_data.cmd->args[1]));
	else
	{
		ft_putstr_fd("exit: ", 1);
		ft_putstr_fd(g_data.cmd->args[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(255);
	}
}
