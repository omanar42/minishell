/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:54:55 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/13 17:15:40 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    ft_child_process(t_cmd *cmd, int i, int size, int *p, int last_fd)
{
    // ignor signals in child process
    if (((t_cmd *)(g_data.cmds->content))->error)
        exit(g_data.exit_status);
    redirect_output();
    close(p[0]);
    if (i != size - 1)
    {
        dup2(p[1], 1);
        close(p[1]);
    }
    if (((t_cmd *)(g_data.cmds->content))->output != 1)
    {
        dup2(((t_cmd *)(g_data.cmds->content))->output, 1);
        close(((t_cmd *)(g_data.cmds->content))->output);
    }
    if (last_fd != -1) 
    {
        dup2(last_fd, 0);
        close(last_fd);
    }
    if (((t_cmd *)(g_data.cmds->content))->input != 0)
    {
        dup2(((t_cmd *)(g_data.cmds->content))->input, 0);
        close(((t_cmd *)(g_data.cmds->content))->input);
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
    // int  status;

    // g_data.tmpin = dup(0);
    // g_data.tmpout = dup(1);
    temp = g_data.cmds;
    len = ft_lstsize(g_data.cmds);
    last_fd = -1;
    redirect_input();
    while(temp)
    {
        pipe(p);
        pid = fork();
        if (pid == 0)
        {
            if (is_builtins())
                ft_builtins();
            else
                ft_child_process((t_cmd *)temp->content, i, len, p, last_fd);
        }
        else
        {
            close(p[1]);
            tmp = g_data.cmds;
            g_data.cmds = g_data.cmds->next;
            temp = temp->next;
            ft_lstdelone(tmp, &free_cmd);
            if(last_fd != -1)
                close(last_fd);
            last_fd = p[0];
            i++;
        }
    }
    // dup2(g_data.tmpin, 0);
    // dup2(g_data.tmpout, 1);
    // close(g_data.tmpin);
    // close(g_data.tmpout);
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
    g_data.tmpin = dup(0);
    g_data.tmpout = dup(1);

	if (((t_cmd *)(g_data.cmds->content))->args[0] == '\0' && ((t_cmd *)(g_data.cmds->content)) == NULL)
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
    dup2(g_data.tmpin, 0);
    dup2(g_data.tmpout, 1);
    close(g_data.tmpin);
    close(g_data.tmpout);
}
