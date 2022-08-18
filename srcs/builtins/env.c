/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:52:39 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/17 23:37:48 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (!env[i])
		return (1); 
	return (0);
}

int	no_env(void)
{
	if (check_path(g_data.env))
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
