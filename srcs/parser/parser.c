/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:59:27 by omanar            #+#    #+#             */
/*   Updated: 2022/08/02 20:29:25 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parsing(char *line, char **env)
{
	t_lexer	*lexer;

	g_data.env = (char **)malloc(sizeof(char *));
	g_data.env[0] = NULL;
	creat_env(env);
	if (unclosed_quotes(line))
	{
		ft_putstr_fd("minishell: syntax error unclosed quotes\n", 2);
		return (1);
	}
	data_init(line);
	lexer = lexer_init(line);
	if (tokens_handler(lexer))
	{
		free(lexer);
		return (1);
	}
	free(lexer);
	return (0);
}
