/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:45:49 by omanar            #+#    #+#             */
/*   Updated: 2022/08/11 18:15:02 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "env\0", 4)
		|| !ft_strncmp(str, "unset\0", 6)
		|| !ft_strncmp(str, "export\0", 7))
		return (1);
	return (0);
}

void	builtins(void)
{
	char	*cmd;
	t_list	*tmp;

	cmd = ((t_cmd *)(g_data.cmds->content))->args[0];
	if (!cmd)
		return ;
	if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		print_env();
	else if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		ft_unset();
	else if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		ft_export();
	tmp = g_data.cmds;
	g_data.cmds = g_data.cmds->next;
	ft_lstdelone(tmp, &free_cmd);
}
