/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:34:41 by omanar            #+#    #+#             */
/*   Updated: 2022/06/21 19:19:10 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parsing(char *line, char **env)
{
	(void)line;
	(void)env;
}

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
		if (!ft_strncmp(line, "exit\0", 5))
			return (printf("exit\n"));
		parsing(line, env);
		free(line);
	}
	return (0);
}
