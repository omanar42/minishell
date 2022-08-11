/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:48:38 by omanar            #+#    #+#             */
/*   Updated: 2022/08/11 18:09:14 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execution(void)
{
	if (is_builtin(((t_cmd *)(g_data.cmds->content))->args[0]))
		builtins();
	// else
	// 	exec_cmds();
}
