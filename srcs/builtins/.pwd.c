/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:52:44 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/20 22:35:32 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd(void)
{
	char	*pwd;
	char	**buff;
	int i;

	i = 0;
	pwd = NULL;
	buff = g_data.env;
	while(buff[i])
	{
		if (ft_strncmp(buff[i], "PWD=", 4) == 0)
		{
			pwd = buff[i] + 4;
			break ;
		}
		i++;
	}
	if (pwd == NULL)
		pwd = getcwd(NULL, 0);
	
	printf("%s\n", pwd);
}
