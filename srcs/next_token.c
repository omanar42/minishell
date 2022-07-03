/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 20:01:36 by omanar            #+#    #+#             */
/*   Updated: 2022/07/03 21:01:26 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token	*next_token(t_lexer *lexer)
{
	if (lexer->c == '<')
	{
		if (lexer_peek(lexer) == '<')
		{
			lexer_advance(lexer);
			lexer_advance(lexer);
			return (init_token("<<", TOKEN_HEREDOC));
		}
		lexer_advance(lexer);
		return (init_token("<", TOKEN_INFILE));
	}
	if (lexer->c == '>')
	{
		if (lexer_peek(lexer) == '>')
		{
			lexer_advance(lexer);
			lexer_advance(lexer);
			return (init_token(">>", TOKEN_AOUT));
		}
		lexer_advance(lexer);
		return (init_token(">", TOKEN_OUTFILE));
	}
	else
		return (lexer_parse(lexer, TOKEN_WORD, 0));
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
	if (lexer->c == '\"' || lexer->c == '\'')
		return (handle_quotes(lexer, TOKEN_WORD, lexer->c));
	else
		return (next_token(lexer));
}
