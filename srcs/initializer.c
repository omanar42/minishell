/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:55:31 by omanar            #+#    #+#             */
/*   Updated: 2022/08/02 20:29:33 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	creat_env(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		tmp = ft_strdup(env[i]);
		g_data.env = advanced_add(g_data.env, tmp);
		free(tmp);
		i++;
	}
}

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
	g_data.cmd->path = NULL;
	g_data.cmd->args = (char **)malloc(sizeof(char *));
	g_data.cmd->args[0] = NULL;
	g_data.cmd->input = 0;
	g_data.cmd->output = 1;
	g_data.cmd->exit_status = 0;
	g_data.cmd->error = 0;
	g_data.cmd->heredoc = 0;
	g_data.cmd->append = 0;
	g_data.cmd->infiles = (char **)malloc(sizeof(char *));
	g_data.cmd->infiles[0] = NULL;
	g_data.cmd->outfiles = (char **)malloc(sizeof(char *));
	g_data.cmd->outfiles[0] = NULL;
}

void	data_init(char *line)
{
	g_data.nb_cmd = get_cmds(line);
	g_data.index = 0;
	g_data.heredoc = 0;
	g_data.err = 0;
	cmd_init();
}
