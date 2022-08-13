/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:15:08 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/13 17:55:29 by adiouane         ###   ########.fr       */
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
    if (!env)
    {
        ft_putstr_fd("minishell: ", 2);
        ft_putstr_fd(((t_cmd *)(g_data.cmds->content))->args[0], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        // exit_code(127);
    }
	while (env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (!env[i])
    {
        g_data.exit_status = 127;
        ft_putstr_fd("minishell: ", 1);
        ft_putstr_fd(((t_cmd *)(g_data.cmds->content))->args[0], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
    }
	else
		return (ft_split(env[i] + 5, ':')); 
	return (NULL);
}

void	run_cmd(t_cmd *cmd)
{
    cmd->paths = get_path(g_data.env);
    cmd->cmd = check_cmd(cmd->paths, cmd->args[0]);
    if (!cmd->cmd)
    {
        g_data.exit_status = 127;
        free_path(cmd->paths);
        error("minishell: command not found ", cmd->args[0], g_data.exit_status);
    }
    if (execve(cmd->cmd, cmd->args, g_data.env) == -1)
    {
        g_data.exit_status = 127;
        free_path(cmd->paths);
        error("minishell: command not found ", cmd->args[0], g_data.exit_status);
    }
}

void    redirect_input()
{
    if (((t_cmd *)(g_data.cmds->content))->input != 0)
    {
        dup2(((t_cmd *)(g_data.cmds->content))->input, 0);
        close(((t_cmd *)(g_data.cmds->content))->input);
    }
}

void    redirect_output(void)
{
    int j = -1;
    while (((t_cmd *)(g_data.cmds->content))->outfiles[++j])
    {
        if (((t_cmd *)(g_data.cmds->content))->append)
            ((t_cmd *)(g_data.cmds->content))->output = open(((t_cmd *)(g_data.cmds->content))->outfiles[j], O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            ((t_cmd *)(g_data.cmds->content))->output = open(((t_cmd *)(g_data.cmds->content))->outfiles[j], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }       
}