/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:16:26 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/28 19:56:41 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	failed_fork(void)
{
	ft_putstr_fd("minishell: ", 2);
	perror("fork");
	g_data.exit_status = 1;
}

void	waiting(int i, int status, int pid)
{
	i = 0;
	while (i < g_data.cmds_size)
	{
		waitpid(-1, &status, 0);
		if (pid != -1)
		{
			g_data.exit_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				g_data.exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
}

void	next_cmd(int last_fd)
{
	t_list	*tmp;

	close(g_data.p[1]);
	tmp = g_data.cmds; // we save address of the current command in tmp to free it later and move to the next command becuse if we don't do that we will lose the address of the current command
	g_data.cmds = g_data.cmds->next; // now we move to the next command in the list
	ft_lstdelone(tmp, &free_cmd); // we delete the current command from the list ; ft_lstdelone(tmp, &free_cmd ) will free the content of the current command and the current command itself
	if (last_fd != -1)
		close(last_fd);
}

void	redirect_input(void)
{
	if (((t_cmd *)(g_data.cmds->content))->input != 0)
	{
		dup2(((t_cmd *)(g_data.cmds->content))->input, 0); // what does dup2 do is that it will copy the file descriptor of the input file to the stdin 
		close(((t_cmd *)(g_data.cmds->content))->input);
	}
}

void	redirect_output(void)
{
	if (((t_cmd *)(g_data.cmds->content))->output != 1)
	{
		dup2(((t_cmd *)(g_data.cmds->content))->output, 1);
		close(((t_cmd *)(g_data.cmds->content))->output);
	}
}
