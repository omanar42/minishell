/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:20:35 by omanar            #+#    #+#             */
/*   Updated: 2022/07/03 22:38:44 by omanar           ###   ########.fr       */
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
