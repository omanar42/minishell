/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 20:01:36 by omanar            #+#    #+#             */
/*   Updated: 2022/07/03 22:39:06 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_charachter(char c, char cc)
{
	if (c == '\0' || c == '|' || c == '<' || c == ' '
		|| c == '>' || (c == '&' && cc == '&'))
		return (0);
	return (1);
}

int	is_quote(char c, char q)
{
	if (c == '\0' || c == q)
		return (0);
	return (1);
}

void	quote_inside(t_lexer *lexer, int *i)
{
	char	q;

	q = lexer->c;
	lexer_advance(lexer);
	(*i)++;
	while (is_quote(lexer->c, q))
	{
		lexer_advance(lexer);
		(*i)++;
	}
}

void	free_token(t_token *token)
{
	free(token->value);
	free(token);
}
