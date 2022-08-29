/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:15:08 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/28 00:16:32 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

void	*check_cmd(char **path, char *cmd)
{
	char	*buff;
	char	*com2;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	if (path == NULL)
		return (NULL);
	while (*path)
	{
		buff = ft_strjoin(*path, "/");
		com2 = ft_strjoin(buff, cmd);
		free(buff);
		if (access(com2, X_OK) == 0)
			return (com2);
		free(com2);
		path++;
	}
	return (NULL);
}

char	**get_path(char **env)
{
	int	i;

	i = 0;
	if (ft_strchr(((t_cmd *)(g_data.cmds->content))->args[0], '/'))
		return (ft_split(((t_cmd *)(g_data.cmds->content))->args[0], ':'));
	while (env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	if (!env[i])
	{
		g_data.exit_status = 127;
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(((t_cmd *)(g_data.cmds->content))->args[0], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(g_data.exit_status);
	}
	else
		return (ft_split(env[i] + 5, ':'));
	return (NULL);
}

void	is_derictory(void)
{
	struct stat	s;
	t_cmd		*cmd;

	cmd = (t_cmd *)(g_data.cmds->content);
	if (ft_strchr(cmd->args[0], '/') || !ft_getenv("PATH="))
	{
		if (stat(cmd->args[0], &s) == 0)
		{
			if (S_ISDIR(s.st_mode))
			{
				g_data.exit_status = 126;
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd->args[0], 2);
				ft_putendl_fd(": is a directory", 2);
				exit(g_data.exit_status);
			}
		}
	}
}

void	run_cmd(t_cmd *cmd)
{
	if (is_builtins_in_child())
		ft_builtins_in_child();
	is_derictory();
	cmd->paths = get_path(g_data.env);
	cmd->cmd = check_cmd(cmd->paths, cmd->args[0]);
	if (!cmd->cmd || !cmd->args[0][0])
	{
		g_data.exit_status = 127;
		free_path(cmd->paths);
		error_command_not_found("minishell:", cmd->args[0], g_data.exit_status);
	}
	else if (execve(cmd->cmd, cmd->args, g_data.env) == -1)
	{
		g_data.exit_status = 127;
		free_path(cmd->paths);
		exit_strerr(cmd->args[0], errno, g_data.exit_status);
	}
}
