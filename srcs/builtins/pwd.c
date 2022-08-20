/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:52:44 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/20 13:53:51 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd(void)
{
	char	*pwd = NULL;
	int i = 0;

	// pwd = getcwd(NULL, 0);
	while(g_data.env[i])
	{
		if (ft_strncmp(g_data.env[i], "PWD=", 4) == 0)
		{
			pwd = g_data.env[i] + 4;
			break ;
		}
		i++;
	}
	printf("%s\n", pwd);
	// free(pwd);
}
