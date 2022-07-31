/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:20:55 by omanar            #+#    #+#             */
/*   Updated: 2022/07/31 17:05:24 by omanar           ###   ########.fr       */
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
	char	*path;
	char	**args;
	int		input;
	int		output;
	int		end[2];
	int		exit_status;
	int		error;
	t_list	*infiles;
	t_list	*outfiles;
	pid_t	pid;
}	t_cmd;

typedef struct s_data {
	char	**env;
	int		nb_cmd;
	int		index;
	int		err;
	int		status_code;
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
int		hundle_infile(t_token *token);
void	token_outfile(t_lexer **lexer, t_token **token);
void	token_appout(t_lexer **lexer, t_token **token);
int		hundle_outfile(t_token *token, int app);

int		argslen(char **args);
char	**advanced_add(char **strs, char *arg);

void	clean(void);
void	free_cmd(void *cmd);
void	free_loop(char **args);
void	free_token(t_token *token);

void	printer(void);

#endif