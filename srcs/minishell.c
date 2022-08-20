/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:34:41 by omanar            #+#    #+#             */
/*   Updated: 2022/08/20 20:02:25 by adiouane         ###   ########.fr       */
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
	init_signal();
	while (42)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
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
