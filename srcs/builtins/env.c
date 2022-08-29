/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:52:39 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/29 22:43:09 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_env(void)
{
	int	i;

	i = 0;
	if (((t_cmd *)(g_data.cmds->content))->args[1] == NULL)
	{
		while (g_data.env[i] != NULL)
		{
			ft_putstr_fd(g_data.env[i], 1);
			ft_putchar_fd('\n', 1);
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
