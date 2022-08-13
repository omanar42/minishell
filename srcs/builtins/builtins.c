/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 21:46:57 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/13 17:49:08 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_builtins(void)
{
	t_list *tmp;
	t_cmd *cmd;

	redirect_input();
	redirect_output();
	if (((t_cmd *)(g_data.cmds->content))->output != 1)
    {
        dup2(((t_cmd *)(g_data.cmds->content))->output, 1);
        close(((t_cmd *)(g_data.cmds->content))->output);
    }
	cmd = (t_cmd *)g_data.cmds->content;
	if (ft_strncmp(cmd->args[0], "pwd", 3) == 0
		|| ft_strncmp(cmd->args[0], "PWD", 3) == 0)
		pwd();
	else if (ft_strncmp(cmd->args[0], "env", 3) == 0
		|| ft_strncmp(cmd->args[0], "ENV", 3) == 0)
		ft_env();
	else if (ft_strncmp(cmd->args[0], "cd", 2) == 0)
		cd();
	else if (ft_strncmp(cmd->args[0], "echo", 4) == 0
		|| ft_strncmp(cmd->args[0], "ECHO", 4) == 0)
		echo();
	else if (ft_strncmp(cmd->args[0], "exit", 4) == 0)
		exit_cmd();
	else if (ft_strncmp(cmd->args[0], "unset", 5) == 0)
		ft_unset();
	else if (ft_strncmp(cmd->args[0], "export", 6) == 0)
		ft_export();
	tmp = g_data.cmds;
	g_data.cmds = g_data.cmds->next;
	ft_lstdelone(tmp, &free_cmd);
}

int	is_builtins(void)
{
	t_cmd *cmd;

	cmd = (t_cmd *)g_data.cmds->content;
	if(!cmd->args[0])
		return (0);
	if ((ft_strncmp(cmd->args[0], "pwd", 3) == 0
		&& ft_strncmp(&cmd->args[0][3], "", 1) == 0) 
		|| (ft_strncmp(cmd->args[0], "PWD", 3) == 0
		&& ft_strncmp(&cmd->args[0][3], "", 1) == 0)
		|| (ft_strncmp(cmd->args[0], "env", 3) == 0
		&& ft_strncmp(&cmd->args[0][3], "", 1) == 0)
		|| (ft_strncmp(cmd->args[0], "ENV", 3) == 0
		&& ft_strncmp(&cmd->args[0][3], "", 1) == 0)
		|| (ft_strncmp(cmd->args[0], "cd", 2) == 0
		&& ft_strncmp(&cmd->args[0][2], "", 1) == 0)
		|| (ft_strncmp(cmd->args[0], "echo", 4) == 0
		&& ft_strncmp(&cmd->args[0][4], "", 1) == 0)
		|| (ft_strncmp(cmd->args[0], "ECHO", 4) == 0
		&& ft_strncmp(&cmd->args[0][4], "", 1) == 0)
		|| (ft_strncmp(cmd->args[0], "exit", 4) == 0
		&& ft_strncmp(&cmd->args[0][4], "", 1) == 0)
		|| (ft_strncmp(cmd->args[0], "unset", 5) == 0
		&& ft_strncmp(&cmd->args[0][5], "", 1) == 0)
		|| (ft_strncmp(cmd->args[0], "export", 6) == 0
		&& ft_strncmp(&cmd->args[0][6], "", 1) == 0))
		return (1);
	return (0);
}
