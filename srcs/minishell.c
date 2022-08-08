/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:34:41 by omanar            #+#    #+#             */
/*   Updated: 2022/08/08 23:18:34 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)av;
	if (ac != 1)
		return (0);
	creat_env(env);
	while (42)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		if (parsing(line))
		{
			free(line);
			clean();
			continue ;
		}
		printer();
		free(line);
	}
	free_loop(g_data.env);
	return (0);
}
