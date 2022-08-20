/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:52:44 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/20 23:41:12 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd(void)
{
	char	*pwd;
	int i;

	i = 0;
	pwd = NULL;
	while(g_data.env[i])
	{
		if (ft_strncmp(g_data.env[i], "PWD=", 4) == 0)
		{
			pwd = ft_strdup(g_data.env[i] + 4);
			break ;
		}
		i++;
	}
	if (!pwd)
		pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_putendl_fd("minishell: pwd: failed to get the current working directory", 2);
	else
		printf("%s\n", pwd);
	free(pwd);
}
