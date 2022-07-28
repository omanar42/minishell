/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 07:41:12 by omanar            #+#    #+#             */
/*   Updated: 2022/07/28 04:23:52 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*init_token(char *value, int type)
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
	{
		lexer_advance(lexer);
		i++;
	}
	while (is_charachter(lexer->c, lexer_peek(lexer)))
	{
		lexer_advance(lexer);
		i++;
	}
	value = ft_substr(lexer->line, start, i);
	token = init_token(value, type);
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
	token = init_token(value, type);
	free(value);
	return (token);
}

t_token	*unexpected_token(t_lexer *lexer)
{
	char	*value;
	t_token	*token;

	lexer_advance(lexer);
	value = ft_substr(lexer->line, lexer->i, 1);
	token = init_token(value, TOKEN_ERROR);
	free(value);
	return (token);
}

t_token	*next_token(t_lexer *lexer)
{
	if (lexer->c == '<')
	{
		if (lexer_peek(lexer) == '<')
		{
			lexer_advance(lexer);
			if (is_unexpected_token(lexer_peek(lexer)))
				return (unexpected_token(lexer));
			lexer_advance(lexer);
			return (init_token("<<", TOKEN_HEREDOC));
		}
		if (is_unexpected_token(lexer_peek(lexer)))
			return (unexpected_token(lexer));
		lexer_advance(lexer);
		return (init_token("<", TOKEN_INFILE));
	}
	if (lexer->c == '>')
	{
		if (lexer_peek(lexer) == '>')
		{
			lexer_advance(lexer);
			if (is_unexpected_token(lexer_peek(lexer)))
				return (unexpected_token(lexer));
			lexer_advance(lexer);
			return (init_token(">>", TOKEN_APPOUT));
		}
		if (is_unexpected_token(lexer_peek(lexer)))
			return (unexpected_token(lexer));
		lexer_advance(lexer);
		return (init_token(">", TOKEN_OUTFILE));
	}
	else
		return (token_parse(lexer, TOKEN_WORD));
}

t_token	*lexer_next_token(t_lexer *lexer)
{
	lexer_skip_whitespace(lexer);
	if (lexer->c == '\0')
		return (init_token(0, TOKEN_EOF));
	if (lexer->c == '&')
	{
		if (is_unexpected_token(lexer_peek(lexer)))
			return (unexpected_token(lexer));
		return (token_parse(lexer, TOKEN_WORD));
	}
	if (lexer->c == '|')
	{
		if (is_unexpected_token(lexer_peek(lexer)))
			return (unexpected_token(lexer));
		lexer_advance(lexer);
		return (init_token("|", TOKEN_PIPE));
	}
	if (lexer->c == '\"' || lexer->c == '\'')
		return (quotes_parse(lexer, TOKEN_WORD, lexer->c));
	else
		return (next_token(lexer));
}
