/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:34:41 by omanar            #+#    #+#             */
/*   Updated: 2022/08/30 17:25:26 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	initialization(char **env)
{
	g_data.exit_status = 0;
	g_data.newpwd = ft_calloc(1, sizeof(char));
	creat_env(env);
	creat_export(g_data.env);
	signal_init();
}

void	last_touch(void)
{
	ft_putstr_fd("exit\n", 1);
	free_loop(g_data.env);
	free_loop(g_data.export);
	exit (g_data.exit_status);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)av;
	if (ac != 1)
		return (0);
	initialization(env);
	while (42)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (line[0] != '\0')
			add_history(line);
		if (parsing(line))
		{
			free(line);
			clean();
			continue ;
		}
		execution();
		free(line);
	}
	last_touch();
	return (0);
}
