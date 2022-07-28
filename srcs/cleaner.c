/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:42:13 by omanar            #+#    #+#             */
/*   Updated: 2022/07/28 22:35:05 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_token(t_token *token)
{
	free(token->value);
	free(token);
}

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
	free_loop(((t_cmd *)cmd)->args);
	free((t_cmd *)cmd);
}

void	clean(void)
{
	t_list	*tmp;

	while (g_data.cmds)
	{
		tmp = g_data.cmds;
		g_data.cmds = g_data.cmds->next;
		ft_lstdelone(tmp, &free_cmd);
	}
}
