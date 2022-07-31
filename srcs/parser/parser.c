/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:59:27 by omanar            #+#    #+#             */
/*   Updated: 2022/07/31 23:43:56 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parsing(char *line, char **env)
{
	t_lexer	*lexer;

	data_init(line);
	(void)env;
	lexer = lexer_init(line);
	if (tokens_handler(lexer))
	{
		free(lexer);
		return (1);
	}
	free(lexer);
	return (0);
}
