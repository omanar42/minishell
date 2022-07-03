/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 05:51:30 by omanar            #+#    #+#             */
/*   Updated: 2022/07/03 21:04:44 by omanar           ###   ########.fr       */
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
		TOKEN_OR_IF,
		TOKEN_AND_IF,
		TOKEN_AOUT,
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

t_token	*init_token(char *value, int type);
t_lexer	*lexer_init(char *line);
t_token	*lexer_next_token(t_lexer *lexer);
void	lexer_skip_whitespace(t_lexer *lexer);
void	lexer_advance(t_lexer *lexer);
char	lexer_peek(t_lexer *lexer);
t_token	*lexer_parse(t_lexer *lexer, int type, int s);
int		get_word_size(char *str);
int		is_charachter(char c, char cc);
t_token	*handle_quotes(t_lexer *lexer, int type, char q);

#endif