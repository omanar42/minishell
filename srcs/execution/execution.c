/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 19:54:55 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/19 20:10:49 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    ft_dup(int olfd, int nfd)
{
    dup2(olfd, nfd);
    close(olfd);
}

void    ft_child_process(t_cmd *cmd, int i, int size, int *p, int last_fd)
{
    open_outputs();
    close(p[0]);
    if (((t_cmd *)(g_data.cmds->content))->error)
        exit(g_data.exit_status);
    if (i != size - 1)
        ft_dup(p[1], 1);
    if (((t_cmd *)(g_data.cmds->content))->output != 1)
        ft_dup(((t_cmd *)(g_data.cmds->content))->output, 1);
    if (last_fd != -1) 
       ft_dup(last_fd, 0);
    if (((t_cmd *)(g_data.cmds->content))->input != 0)
        ft_dup(((t_cmd *)(g_data.cmds->content))->input, 0);
    run_cmd(cmd);
}

void    run_execution(void)
{ 
    t_list *tmp;
    pid_t pid;
    int i = 0;
    int len = 0;
    int p[2];
    int last_fd;
    int  status;

    len = ft_lstsize(g_data.cmds);
    last_fd = -1;
    redirect_input();
    while(g_data.cmds)
    {
        pipe(p);
        signal(SIGQUIT, SIG_IGN);
        g_data.signalchild = 1;
        pid = fork();
        if (pid == -1)
            error1("Failed to fork process", errno);
        if (pid == 0)
        {
            g_data.signalqiut = 1;
            g_data.signalchild = 1;
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            ft_child_process((t_cmd *)g_data.cmds->content, i, len, p, last_fd);
        }
        else
        {
            close(p[1]);
            tmp = g_data.cmds;
            g_data.cmds = g_data.cmds->next;
            ft_lstdelone(tmp, &free_cmd);
            if (last_fd != -1)
                close(last_fd);
            last_fd = p[0];
            i++;
        }
    }
    i = 0;
    while (i < len)
    {
        waitpid(-1, &status, 0);
        g_data.exit_status = WEXITSTATUS(status); //WEXITSTATUS returns the exit status of the child process
        if (WIFSIGNALED(status))
            g_data.exit_status = 128 + WTERMSIG(status);
        i++;
    }
}

void	execution(void)
{
    g_data.tmpin = dup(0);
    g_data.tmpout = dup(1);

	if (!g_data.cmds->next && is_builtins())
		ft_builtins();
	else
		run_execution();
    g_data.signalchild = 0;
    dup2(g_data.tmpin, 0);
    dup2(g_data.tmpout, 1);
    close(g_data.tmpin);
    close(g_data.tmpout);
}
