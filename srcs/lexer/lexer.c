/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:20:35 by omanar            #+#    #+#             */
/*   Updated: 2022/07/28 23:06:05 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_lexer	*lexer_init(char *line)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->line = line;
	lexer->i = 0;
	lexer->c = line[lexer->i];
	lexer->size = ft_strlen(lexer->line);
	return (lexer);
}

t_token	*token_init(char *value, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (!value)
		token->value = NULL;
	else
		token->value = ft_strdup(value);
	token->e_type = type;
	return (token);
}

void	lexer_advance(t_lexer *lexer)
{
	if (lexer->i < lexer->size && lexer->c != '\0')
	{
		lexer->i++;
		lexer->c = lexer->line[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t'
		|| lexer->c == 13 || lexer->c == 10)
		lexer_advance(lexer);
}

char	lexer_peek(t_lexer *lexer)
{
	if (lexer->i < lexer->size)
		return (lexer->line[lexer->i + 1]);
	return ('\0');
}
