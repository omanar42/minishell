/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:59:27 by omanar            #+#    #+#             */
/*   Updated: 2022/07/31 19:24:50 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	dollar_parsing(t_lexer *lexer, t_token *token)
{
	(void)lexer;
	(void)token;
}

void	quotes_parsing(t_lexer *lexer, t_token *token)
{
	int		i;
	char	**args;

	i = 0;
	if (ft_strchr(token->value, '$'))
		dollar_parsing(lexer, token);
	else
	{
		args = ft_split(token->value, '"');
		while (args[i])
		{
			if (args[i][0] == '$')
				dollar_parsing(lexer, token);
			if (i == 0)
				((t_cmd *)(g_data.cmds->content))->cmd = args[i];
			else
				((t_cmd *)(g_data.cmds->content))->args[i] = args[i];
			i++;
		}
	}
}

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
