/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:01:23 by omanar            #+#    #+#             */
/*   Updated: 2022/07/24 19:17:22 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	printer(void)
{
	int	i, j;

	i = 0;
	while (i < ft_lstsize(g_data.cmds))
	{
		printf("------------------ CMD %d ------------------\n\n", i + 1);
		printf("==========>   Commande = %s   <==========\n", ((t_cmd *)(g_data.cmds->content))->cmd);
		printf("");
		j = -1;
		while (((t_cmd *)(g_data.cmds->content))->args[++j])
			printf("==========>   Arg[%d] = %s   <==========\n", j, ((t_cmd *)(g_data.cmds->content))->args[j]);
		printf("\n------------------------------------------\n\n\n");
		g_data.cmds = g_data.cmds->next;
		i++;
	}
}
