/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:55:31 by omanar            #+#    #+#             */
/*   Updated: 2022/08/21 19:12:06 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	creat_env(char **env)
{
	int		i;

	i = -1;
	g_data.exit_status = 0;
	g_data.env = (char **)malloc(sizeof(char *));
	g_data.env[0] = NULL;
	while (env[++i])
		g_data.env = advanced_add(g_data.env, env[i]);
}

void	creat_export(char **env)
{
	int		i;
	char	*tmp;
	char	*vtmp;
	char	*value;

	i = -1;
	g_data.export = ft_calloc(1, sizeof(char *));
	while (env[++i])
	{
		tmp = NULL;
		tmp = advanced_join(tmp, "declare -x ");
		vtmp = get_variable_name(env[i]);
		tmp = advanced_join(tmp, vtmp);
		free(vtmp);
		tmp = advanced_join(tmp, "=\"");
		value = ft_strdup(env[i] + get_char_index(env[i], '=') + 1);
		tmp = advanced_join(tmp, value);
		free(value);
		tmp = advanced_join(tmp, "\"");
		g_data.export = advanced_add(g_data.export, tmp);
		free(tmp);
	}
}

void	cmd_init(void)
{
	g_data.cmd = (t_cmd *)malloc(sizeof(t_cmd));
	g_data.cmd->cmd = NULL;
	g_data.cmd->args = (char **)malloc(sizeof(char *));
	g_data.cmd->args[0] = NULL;
	g_data.cmd->input = 0;
	g_data.cmd->infile = NULL;
	g_data.cmd->output = 1;
	g_data.cmd->append = ft_calloc(1, sizeof(int));
	g_data.cmd->app_index = -1;
	g_data.cmd->error = 0;
	g_data.cmd->exit_status = 0;
	g_data.cmd->outfiles = (char **)malloc(sizeof(char *));
	g_data.cmd->outfiles[0] = NULL;
}

void	data_init(void)
{
	g_data.error = 0;
	g_data.dollar = 0;
	g_data.signalchild = 0;
	g_data.breaker = 0;
	g_data.signal_heredoc = 0;
	cmd_init();
}
