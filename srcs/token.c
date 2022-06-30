/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 07:41:12 by omanar            #+#    #+#             */
/*   Updated: 2022/06/30 07:55:41 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_charachter(char c, char cc)
{
	if (c == '\0' || c == '|' || c == '<'
		|| c == '>' || (c == '&' && cc == '&'))
		return (0);
	return (1);
}

int	get_word_size(char *str)
{
	int	size;

	size = 0;
	while (str[size] != '\0' && is_charachter(str[size], str[size + 1]))
		size++;
	return (size);
}

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->e_type = type;
	return (token);
}

t_token	*lexer_next_token(t_lexer *lexer)
{
	lexer_skip_whitespace(lexer);
	if (lexer->c == '\0')
		return (init_token(0, TOKEN_EOF));
	if (lexer->c == '&' && lexer_peek(lexer) == '&')
	{
		lexer_advance(lexer);
		lexer_advance(lexer);
		return (init_token("&&", TOKEN_AND_IF));
	}
	if (lexer->c == '|')
	{
		if (lexer_peek(lexer) == '|')
		{
			lexer_advance(lexer);
			lexer_advance(lexer);
			return (init_token("||", TOKEN_OR_IF));
		}
		lexer_advance(lexer);
		return (init_token("|", TOKEN_PIPE));
	}
	if (lexer->c == '<')
	{
		if (lexer_peek(lexer) == '<')
		{
			lexer_advance(lexer);
			lexer_advance(lexer);
			return (lexer_parse(lexer, TOKEN_HEREDOC, 1));
		}
		lexer_advance(lexer);
		return (lexer_parse(lexer, TOKEN_INFILE, 1));
	}
	if (lexer->c == '>')
	{
		if (lexer_peek(lexer) == '>')
		{
			lexer_advance(lexer);
			lexer_advance(lexer);
			return (lexer_parse(lexer, TOKEN_AOUT, 1));
		}
		lexer_advance(lexer);
		return (lexer_parse(lexer, TOKEN_OUTFILE, 1));
	}
	else
		return (lexer_parse(lexer, TOKEN_WORD, 0));
}
