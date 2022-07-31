/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:20:55 by omanar            #+#    #+#             */
/*   Updated: 2022/08/01 00:21:12 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <lexer.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>

# define RST "\033[0m"
# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define CYN "\033[0;36m"

typedef struct s_cmd
{
	char	*path;
	char	**args;
	int		input;
	int		output;
	int		end[2];
	int		heredoc;
	int		exit_status;
	int		error;
	char	**infiles;
	char	**outfiles;
	int		append;
	pid_t	pid;
}	t_cmd;

typedef struct s_data {
	char	**env;
	int		nb_cmd;
	int		index;
	int		err;
	int		heredoc;
	t_cmd	*cmd;
	t_list	*cmds;
	t_list	*limiter;
}	t_data;

t_data	g_data;

int		parsing(char *line, char **env);
void	quotes_parsing(t_lexer *lexer, t_token *token);
void	dollar_parsing(t_lexer *lexer, t_token *token);

void	data_init(char *line);
void	cmd_init(void);
int		get_cmds(char *line);

int		tokens_handler(t_lexer *lexer);
int		token_error(t_token *token);
void	hundle_word(t_token *token);
void	hundle_pipe(void);
void	token_infile(t_lexer **lexer, t_token **token);
void	token_outfile(t_lexer **lexer, t_token **token);

int		argslen(char **args);
char	**advanced_add(char **strs, char *arg);

void	clean(void);
void	free_cmd(void *cmd);
void	free_loop(char **args);
void	free_token(t_token *token);

void	printer(void);

void	do_heredoc(t_lexer **lexer, t_token **token);

#endif