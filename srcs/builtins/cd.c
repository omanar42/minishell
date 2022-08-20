/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:57:11 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/20 14:27:42 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*ft_getenv(char *str)
{
	int	i;

	i = 0;
	if (!g_data.env)
		return (NULL);
	while (g_data.env[i] != NULL)
	{
		if (ft_strncmp(g_data.env[i], str, ft_strlen(str)) == 0)
			return (g_data.env[i] + ft_strlen(str));
		i++;
	}
	return (NULL);
}

void	setnewpwd(char *newpwd)
{
	int	i;

	i = 0;
	while (g_data.env[i] != NULL)
	{
		if (ft_strncmp(g_data.env[i], "PWD=", 4) == 0)
		{
			free(g_data.env[i]);
			g_data.env[i] = ft_strjoin("PWD=", newpwd);
			return ;
		}
		i++;
	}
}

void	setoldpwd(char *oldpwd)
{
	int	i;

	i = 0;
	while (g_data.env[i] != NULL)
	{
		if (ft_strncmp(g_data.env[i], "OLDPWD=", 7) == 0)
		{
			free(g_data.env[i]);
			g_data.env[i] = ft_strjoin("OLDPWD=", oldpwd);
			return ;
		}
	i++;
	}
}

void	*cd_only(char *path)
{
	path = ft_getenv("HOME=");
	if (path == NULL)
	{
		g_data.exit_status =  1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (path);
}

void	cd(void)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	path = NULL;
	oldpwd = getcwd(NULL, 0);
	if (((t_cmd *)(g_data.cmds->content))->args[1] == NULL)
		path = cd_only(path);
	else
		path = ((t_cmd *)(g_data.cmds->content))->args[1];
	if (chdir(path) == -1 && path)
	{
		g_data.exit_status = 1;
		ft_putstr_fd("minishell: cd: no such file or directory: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd("\n", 2);
	}
	newpwd = getcwd(NULL, 0);
	setnewpwd(newpwd);
	setoldpwd(oldpwd);
	free(oldpwd);
	free(newpwd);
}
