/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:55:31 by omanar            #+#    #+#             */
/*   Updated: 2022/07/28 04:07:42 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_cmds(char *line)
{
	int	i;
	int	nb_cmd;

	i = 0;
	nb_cmd = 1;
	while (line[i])
	{
		if ((line[i] == '|' && line[i + 1] == '|')
			&& (line[i] == '&' && line[i + 1] == '&'))
		{
			i++;
			nb_cmd++;
		}
		if (line[i] == '|')
			nb_cmd++;
		i++;
	}
	return (nb_cmd);
}

void	cmd_init(void)
{
	g_data.cmd = (t_cmd *)malloc(sizeof(t_cmd));
	g_data.cmd->cmd = NULL;
	g_data.cmd->path = NULL;
	g_data.cmd->args = (char **)malloc(sizeof(char *));
	g_data.cmd->args[0] = NULL;
	g_data.cmd->input = 0;
	g_data.cmd->output = 1;
	g_data.cmd->exit_status = 0;
	g_data.cmd->error = 0;
}

void	data_init(char *line)
{
	g_data.nb_cmd = get_cmds(line);
	g_data.index = 0;
	cmd_init();
}
