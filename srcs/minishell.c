/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:34:41 by omanar            #+#    #+#             */
/*   Updated: 2022/08/12 22:19:54 by adiouane         ###   ########.fr       */
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
	creat_export(g_data.env);
	while (42)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (line[0] == '\0')
			continue ;
		add_history(line);
		if (parsing(line))
		{
			free(line);
			clean();
			continue ;
		}
		// printer();
		execution();
		free(line);
	}
	free_loop(g_data.env);
	return (0);
}
