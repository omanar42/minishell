/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 07:41:12 by omanar            #+#    #+#             */
/*   Updated: 2022/07/03 20:01:14 by omanar           ###   ########.fr       */
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

int	is_char(char c, char q)
{
	if (c == '\0' || c == q)
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
	if (!value)
		token->value = NULL;
	else
		token->value = ft_strdup(value);
	token->e_type = type;
	return (token);
}

t_token	*handle_quotes(t_lexer *lexer, int type, char q)
{
	int		i;
	int		start;
	char	*value;

	i = 1;
	start = lexer->i;
	lexer_advance(lexer);
	while (is_char(lexer->c, q))
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
	return (init_token(value, type));
}
