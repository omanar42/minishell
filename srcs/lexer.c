/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:20:35 by omanar            #+#    #+#             */
/*   Updated: 2022/07/03 21:00:36 by omanar           ###   ########.fr       */
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

char	lexer_peek(t_lexer *lexer)
{
	if (lexer->i < lexer->size)
		return (lexer->line[lexer->i + 1]);
	return ('\0');
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == ' ' || lexer->c == '\t'
		|| lexer->c == 13 || lexer->c == 10)
		lexer_advance(lexer);
}

t_token	*lexer_parse(t_lexer *lexer, int type, int s)
{
	char	*value;
	t_token	*token;
	int		i;

	i = 0;
	lexer_skip_whitespace(lexer);
	value = malloc(sizeof(char) * get_word_size(&lexer->line[lexer->i]) + 1);
	if (!value)
		return (NULL);
	while (is_charachter(lexer->c, lexer_peek(lexer)))
	{
		if (lexer->c == ' ' && s == 1)
		{
			lexer_skip_whitespace(lexer);
			break ;
		}
		value[i] = lexer->c;
		lexer_advance(lexer);
		i++;
	}
	value[i] = '\0';
	token = init_token(value, type);
	free(value);
	return (token);
}
