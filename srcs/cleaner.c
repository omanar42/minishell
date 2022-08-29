/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:42:13 by omanar            #+#    #+#             */
/*   Updated: 2022/08/23 18:45:14 by adiouane         ###   ########.fr       */
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

	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}

void	free_cmd(void *cmd)
{
	free(((t_cmd *)cmd)->cmd);
	free(((t_cmd *)cmd)->infile);
	free(((t_cmd *)cmd)->append);
	free_loop(((t_cmd *)cmd)->args);
	free_loop(((t_cmd *)cmd)->outfiles);
	free((t_cmd *)cmd);
}

void	clean(void)
{
	t_list	*tmp;

	if (g_data.cmds)
	{
		while (g_data.cmds)
		{
			tmp = g_data.cmds;
			g_data.cmds = g_data.cmds->next;
			ft_lstdelone(tmp, &free_cmd);
		}
	}
	else
		free_cmd(g_data.cmd);
}
