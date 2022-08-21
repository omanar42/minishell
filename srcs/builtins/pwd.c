/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:52:44 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/21 03:53:24 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	pwd(void)
{
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_putendl_fd("minishell: pwd: failed to get the current working directory", 2);
	else
		printf("%s\n", pwd);
	free(pwd);
}
