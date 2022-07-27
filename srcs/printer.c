/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:01:23 by omanar            #+#    #+#             */
/*   Updated: 2022/07/26 22:21:42 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	printer(void)
{
	int	i;
	int	j;

	i = 0;
	while (g_data.cmds)
	{	
		printf("------------------ CMD %d ------------------\n\n", i + 1);
		printf("==========>   Commande = %s   <==========\n",
			((t_cmd *)(g_data.cmds->content))->cmd);
		printf("");
		j = -1;
		while (((t_cmd *)(g_data.cmds->content))->args[++j])
			printf("==========>   Arg[%d] = %s   <==========\n",
				j, ((t_cmd *)(g_data.cmds->content))->args[j]);
		printf("==========>   INPUT = %d   <==========\n",
			((t_cmd *)(g_data.cmds->content))->input);
		printf("==========>   OUTPUT = %d   <==========\n",
			((t_cmd *)(g_data.cmds->content))->output);
		printf("\n------------------------------------------\n\n\n");
		// system("leaks -q minishell");
		ft_lstdelone(g_data.cmds, &free_cmd);
		// free_cmd(g_data.cmds->content);
		g_data.cmds = g_data.cmds->next;
		i++;
	}
	// free(g_data.cmds);
}
