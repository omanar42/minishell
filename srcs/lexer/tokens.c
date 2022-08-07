/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 07:41:12 by omanar            #+#    #+#             */
/*   Updated: 2022/08/07 15:36:50 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*quotes_parse(t_lexer *lexer, int type, char q)
{
	int		i;
	int		start;
	char	*value;
	t_token	*token;

	i = 1;
	start = lexer->i;
	lexer_advance(lexer);
	while (is_quote(lexer->c, q))
		(lexer_advance(lexer), i++);
	while (is_charachter(lexer->c, lexer_peek(lexer)))
	{
		(lexer_advance(lexer), i++);
		if (lexer->c == '"' || lexer->c == '\'')
		{
			q = lexer->c;
			(lexer_advance(lexer), i++);
			while (is_quote(lexer->c, q))
				(lexer_advance(lexer), i++);
		}
	}
	value = ft_substr(lexer->line, start, i);
	token = token_init(value, type);
	free(value);
	return (token);
}

t_token	*token_parse(t_lexer *lexer, int type)
{
	int		i;
	int		start;
	char	*value;
	t_token	*token;

	i = 0;
	start = lexer->i;
	lexer_skip_whitespace(lexer);
	while (lexer->c != '\0' && is_charachter(lexer->c, lexer_peek(lexer)))
	{
		if (lexer->c == '"' || lexer->c == '\'')
			quote_inside(lexer, &i);
		lexer_advance(lexer);
		i++;
	}
	value = ft_substr(lexer->line, start, i);
	token = token_init(value, type);
	free(value);
	return (token);
}

t_token	*token_file(t_lexer *lexer)
{
	if (lexer_peek(lexer) == '>')
	{
		lexer_advance(lexer);
		while (lexer_peek(lexer) == ' ' || lexer_peek(lexer) == '\t')
			lexer_advance(lexer);
		if (is_unexpected_token(lexer_peek(lexer)))
			return (unexpected_token(lexer));
		lexer_advance(lexer);
		return (token_init(">>", TOKEN_APP));
	}
	while (lexer_peek(lexer) == ' ' || lexer_peek(lexer) == '\t')
		lexer_advance(lexer);
	if (is_unexpected_token(lexer_peek(lexer)))
		return (unexpected_token(lexer));
	lexer_advance(lexer);
	return (token_init(">", TOKEN_OUT));
}

t_token	*next_token(t_lexer *lexer)
{
	if (lexer->c == '\"' || lexer->c == '\'')
		return (quotes_parse(lexer, TOKEN_WORD, lexer->c));
	if (lexer->c == '<')
	{
		if (lexer_peek(lexer) == '<')
		{
			lexer_advance(lexer);
			while (lexer_peek(lexer) == ' ' || lexer_peek(lexer) == '\t')
				lexer_advance(lexer);
			if (is_unexpected_token(lexer_peek(lexer)))
				return (unexpected_token(lexer));
			lexer_advance(lexer);
			return (token_init("<<", TOKEN_HEREDOC));
		}
		while (lexer_peek(lexer) == ' ' || lexer_peek(lexer) == '\t')
			lexer_advance(lexer);
		if (is_unexpected_token(lexer_peek(lexer)))
			return (unexpected_token(lexer));
		lexer_advance(lexer);
		return (token_init("<", TOKEN_INFILE));
	}
	if (lexer->c == '>')
		return (token_file(lexer));
	else
		return (token_parse(lexer, TOKEN_WORD));
}

t_token	*lexer_next_token(t_lexer *lexer)
{
	lexer_skip_whitespace(lexer);
	if (lexer->c == '\0')
		return (token_init(0, TOKEN_EOF));
	if (lexer->c == '&')
	{
		while (lexer_peek(lexer) == ' ' || lexer_peek(lexer) == '\t')
			lexer_advance(lexer);
		if (is_unexpected_token(lexer_peek(lexer)))
			return (unexpected_token(lexer));
		return (token_parse(lexer, TOKEN_WORD));
	}
	if (lexer->c == '|')
	{
		while (lexer_peek(lexer) == ' ' || lexer_peek(lexer) == '\t')
			lexer_advance(lexer);
		if (lexer_peek(lexer) == '|' || lexer_peek(lexer) == '&'
			|| lexer_peek(lexer) == '\0' || lexer_peek(lexer) == '('
			|| lexer_peek(lexer) == ')' || lexer_peek(lexer) == '\n')
			return (unexpected_token(lexer));
		lexer_advance(lexer);
		return (token_init("|", TOKEN_PIPE));
	}
	else
		return (next_token(lexer));
}
