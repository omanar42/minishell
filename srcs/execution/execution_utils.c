/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:15:08 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/11 23:15:37 by adiouane         ###   ########.fr       */
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
        ft_putstr_fd(g_data.cmd->args[0], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        // exit_code(127);
    }
	while (env[i] && ft_strnstr(env[i], "PATH", 4) == 0)
		i++;
	if (!env[i])
    {
        ft_putstr_fd("minishell: ", 1);
        ft_putstr_fd(g_data.cmd->args[0], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
    }
	else
		return (ft_split(env[i] + 5, ':'));
	return (NULL);
}