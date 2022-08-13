/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:10:33 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/13 17:53:14 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exit_cmd(void)
{
    // overlap
	if (((t_cmd *)(g_data.cmds->content))->args[1] == NULL)
		exit(g_data.exit_status); // exit last cmd globle exit status_code
	else if (((t_cmd *)(g_data.cmds->content))->args[1] != NULL && ft_isdigit(((t_cmd *)(g_data.cmds->content))->args[1][0]))
	{
		g_data.exit_status = 1;
		ft_putstr_fd("exit \n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	else if (ft_isdigit(((t_cmd *)(g_data.cmds->content))->args[1][0]))
		exit(ft_atoi(((t_cmd *)(g_data.cmds->content))->args[1]));
	else
	{
		ft_putstr_fd("exit: ", 1);
		ft_putstr_fd(((t_cmd *)(g_data.cmds->content))->args[1], 1);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_data.exit_status = 225;
		exit(g_data.exit_status);
	}
}
