/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:54:55 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/11 23:34:05 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	run_cmd(t_cmd *cmd)
{
    cmd->paths = get_path(g_data.env);
    cmd->cmd = check_cmd(cmd->paths, cmd->args[0]);
    if (!cmd->cmd)
    {
        free_path(cmd->paths);
        error("minishell: command not found ", cmd->args[0], 127);
    }
    if (execve(cmd->cmd, cmd->args, g_data.env) == -1)
    {
        free_path(cmd->paths);
        error("minishell: command not found ", cmd->args[0], 127);
    }
}

void    rederict_fils()
{
    int j = -1;
    while (((t_cmd *)(g_data.cmds->content))->outfiles[++j])
    {
        if (((t_cmd *)(g_data.cmds->content))->append)
            ((t_cmd *)(g_data.cmds->content))->output = open(((t_cmd *)(g_data.cmds->content))->outfiles[j], O_WRONLY | O_CREAT | O_APPEND, 0644);
        else
            ((t_cmd *)(g_data.cmds->content))->output = open(((t_cmd *)(g_data.cmds->content))->outfiles[j], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }       
    if (((t_cmd *)(g_data.cmds->content))->input != 0)
    {
        dup2(((t_cmd *)(g_data.cmds->content))->input, 0);
        close(((t_cmd *)(g_data.cmds->content))->input);
    }
    if (((t_cmd *)(g_data.cmds->content))->output != 1)
    {
        dup2(((t_cmd *)(g_data.cmds->content))->output, 1);
        close(((t_cmd *)(g_data.cmds->content))->output);
    }
}

void    ft_child_process(t_cmd *cmd, int i, int size, int *p, int last_fd)
{
    close(p[0]);
    if (i != size - 1)
    {
        rederict_fils();
        dup2(p[1], 1);
    }
    if (last_fd != -1) 
    {
        dup2(last_fd, 0);
        int j = -1;
        while (((t_cmd *)(g_data.cmds->content))->outfiles[++j])
        {
            if (((t_cmd *)(g_data.cmds->content))->append)
                ((t_cmd *)(g_data.cmds->content))->output = open(((t_cmd *)(g_data.cmds->content))->outfiles[j], O_WRONLY | O_CREAT | O_APPEND, 0644);
            else
                ((t_cmd *)(g_data.cmds->content))->output = open(((t_cmd *)(g_data.cmds->content))->outfiles[j], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        }       
        if (((t_cmd *)(g_data.cmds->content))->output != 1)
        {
            dup2(((t_cmd *)(g_data.cmds->content))->output, 1);
            close(((t_cmd *)(g_data.cmds->content))->output);
        }
    }
    run_cmd(cmd);
}

void    run_execution(void)
{ 
    t_list *temp;
    t_list *tmp;
    pid_t pid;
    int i = 0;
    int len = 0;
    int p[2];
    int last_fd;

    g_data.tmpin = dup(0);
    g_data.tmpout = dup(1);
    temp = g_data.cmds;
    len = ft_lstsize(g_data.cmds);
    last_fd = -1;
    if (((t_cmd *)(g_data.cmds->content))->input != 0)
    {
        dup2(((t_cmd *)(g_data.cmds->content))->input, 0);
        close(((t_cmd *)(g_data.cmds->content))->input);
    }
    while(temp)
    {
        pipe(p);
        pid = fork();
        if (pid == 0)
            ft_child_process((t_cmd *)temp->content, i, len, p, last_fd);
        else
        {
            close(p[1]);
            tmp = g_data.cmds;
            g_data.cmds = g_data.cmds->next;
            ft_lstdelone(tmp, &free_cmd);
            temp = temp->next;
            if(last_fd != -1)
                close(last_fd);
            last_fd = p[0];
            i++;
        }
    }
    dup2(g_data.tmpin, 0);
    dup2(g_data.tmpout, 1);
    close(g_data.tmpin);
    close(g_data.tmpout);
    i = 0;
    while (i < len)
    {
        waitpid(-1, NULL, 0);
        i++;
    }
}

void	execution(void)
{
	t_list *tmp;
	
	g_data.number_of_commend = ft_lstsize(g_data.cmds);

	if (((t_cmd *)(g_data.cmds->content))->args[0] == '\0')
	{
		tmp = g_data.cmds;
		g_data.cmds = g_data.cmds->next;
		ft_lstdelone(tmp, &free_cmd);
		return ;
	}
	else if (is_builtins())
		ft_builtins();
	else
		run_execution(); 
}
