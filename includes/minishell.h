/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:20:55 by omanar            #+#    #+#             */
/*   Updated: 2022/08/09 19:17:38 by omanar           ###   ########.fr       */
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
	char	*cmd;
	char	**args;
	int		end[2];
	int		input;
	char	*infile;
	int		output;
	char	**outfiles;
	int		append;
	int		error;
	int		exit_status;
	pid_t	pid;
}	t_cmd;

typedef struct s_data {
	char	**env;
	int		error;
	int		exit_status;
	t_cmd	*cmd;
	t_list	*cmds;
}	t_data;

t_data	g_data;

int		parsing(char *line);
int		unclosed_quotes(char *line);
void	creat_env(char **env);
void	data_init(void);
void	cmd_init(void);

int		tokens_handler(t_lexer *lexer);
int		token_error(t_token *token);
void	token_word(t_token **token);
void	token_outfile(t_lexer **lexer, t_token **token);
void	token_infile(t_lexer **lexer, t_token **token);
int		open_infile(t_token *token);
void	token_heredoc(t_lexer **lexer, t_token **token);
void	open_heredoc(char *value, int expand);
void	token_pipe(void);

char	*parse_args(char *str);
char	*parse_dquote(char *str, int *i);
char	*parse_squote(char *str, int *i);
char	*parse_dollar(char *str, int *i);
char	*parse_buff(char *buff);
char	*parse_limiter(char *str, int *expand);
char	*expand_dollar(char *str, char **env);
char	*handle_spaces(char *value, char **new);
char	*get_variable_name(char *str);
char	*advanced_join(char *s1, char *s2);
char	**advanced_add(char **strs, char *arg);

int		argslen(char **args);
int		is_acceptable(char c);
int		is_separator(char c);
int		get_char_index(char *str, char c);

void	clean(void);
void	free_cmd(void *cmd);
void	free_loop(char **args);
void	free_token(t_token *token);

void	printer(void);
void	print_env(void);

#endif