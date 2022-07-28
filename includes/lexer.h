/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 05:51:30 by omanar            #+#    #+#             */
/*   Updated: 2022/07/28 02:32:22 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H 

typedef struct s_token
{
	enum {
		TOKEN_EOF,
		TOKEN_WORD,
		TOKEN_PIPE,
		TOKEN_ERROR,
		TOKEN_OR_IF,
		TOKEN_AND_IF,
		TOKEN_APPOUT,
		TOKEN_INFILE,
		TOKEN_OUTFILE,
		TOKEN_HEREDOC,
	}	e_type;
	char	*value;
}	t_token;

typedef struct s_lexer
{
	int		i;
	int		size;
	char	c;
	char	*line;
}	t_lexer;

t_lexer	*lexer_init(char *line);
void	lexer_advance(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
char	lexer_peek(t_lexer *lexer);
t_token	*init_token(char *value, int type);
t_token	*lexer_next_token(t_lexer *lexer);
t_token	*next_token(t_lexer *lexer);
t_token	*token_parse(t_lexer *lexer, int type);
t_token	*quotes_parse(t_lexer *lexer, int type, char q);
t_token	*unexpected_token(t_lexer *lexer);
void	free_token(t_token *token);
void	quote_inside(t_lexer *lexer, int *i);
int		is_quote(char c, char q);
int		is_charachter(char c, char cc);
int		is_unexpected_token(char c);

#endif