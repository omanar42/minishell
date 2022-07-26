/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:42:13 by omanar            #+#    #+#             */
/*   Updated: 2022/07/26 14:54:57 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_loop(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_cmd(void *cmd)
{
	free(((t_cmd *)cmd)->cmd);
	free(((t_cmd *)cmd)->path);
	free(((t_cmd *)cmd)->input);
	free(((t_cmd *)cmd)->output);
	free_loop(((t_cmd *)cmd)->args);
	free((t_cmd *)cmd);
}

void	clean(void)
{
	while (g_data.cmds)
	{
		ft_lstdelone(g_data.cmds, &free_cmd);
		g_data.cmds = g_data.cmds->next;
	}
}
