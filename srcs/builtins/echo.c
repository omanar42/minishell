/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:09:42 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/13 08:48:49 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_flag(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (args[i] != NULL)
	{
		if (ft_strncmp(&args[i][0], "-", 1) == 0
			&& ft_strncmp(&args[i][1], "n", 1) == 0)
		{
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] == '\0')
				return (1);
			else
				return (0);
		}
		else
			return (0);
		i++;
	}
	return (0);
}

void	echo(void)
{
	int	i;

	i = 1;
	if (g_data.cmd->args[1] == NULL)
	{
		printf("\n");
		return ;
	}
	while (is_flag(&g_data.cmd->args[i]) == 1)
		i++;
	g_data.flag = i;
	while (g_data.cmd->args[i])
	{
		ft_putstr_fd(g_data.cmd->args[i], 1);
		ft_putstr_fd(" ", 1);
		i++;
	}
	if (g_data.flag == 1)
		ft_putstr_fd("\n", 1);
	g_data.exit_status = 0;
}
