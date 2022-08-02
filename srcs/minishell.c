/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:34:41 by omanar            #+#    #+#             */
/*   Updated: 2022/08/02 20:02:36 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// system("leaks -q minishell");
// clean();

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)av;
	if (ac != 1)
		return (0);
	while (42)
	{
		line = readline(GRN "➜ " CYN " minishell$ " RST);
		if (!line)
			continue ;
		add_history(line);
		if (parsing(line, env))
		{
			free(line);
			clean();
			continue ;
		}
		printer();
		free_loop(g_data.env);
		free(line);
	}
	return (0);
}
