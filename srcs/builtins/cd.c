/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:57:11 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/20 23:24:04 by omanar           ###   ########.fr       */
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

void	set_pwd(char *newpwd, char *oldpwd)
{
	ft_set_env("PWD", newpwd);
	ft_set_export("PWD", newpwd, 1);
	ft_set_env("OLDPWD", oldpwd);
	ft_set_export("OLDPWD", oldpwd, 1);
}

void	*cd_only(char *path)
{
	path = ft_getenv("HOME=");
	if (path == NULL)
	{
		g_data.exit_status = 1;
		ft_putendl_fd("minishell: cd: HOME not set", 2);
		return (NULL);
	}
	return (path);
}

void	getcwd_error(int err)
{
	g_data.exit_status = 0;
	ft_putstr_fd("cd: error retrieving current directory: getcwd: cannot access parent directories: ", 2);
	ft_putendl_fd(strerror(err), 2);
	chdir("..");
}

void	cd(void)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	path = NULL;
	if (((t_cmd *)(g_data.cmds->content))->args[1] == NULL)
		path = cd_only(path);
	else
		path = ((t_cmd *)(g_data.cmds->content))->args[1];
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		getcwd_error(errno);
	if (chdir(path) == -1 && path)
	{
		ft_putstr_fd("Minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		g_data.exit_status = 1;
	}
	newpwd = getcwd(NULL, 0);
	set_pwd(newpwd, oldpwd);
	free(oldpwd);
	free(newpwd);
}
