/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:20:55 by omanar            #+#    #+#             */
/*   Updated: 2022/08/11 23:20:54 by adiouane         ###   ########.fr       */
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
# include <signal.h>

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
	/*********/
	int		fd_p[2];
	char	**paths;
	int 	last_cmd;
	int		first_cmd;
	char	**cmd_arg;
	int		n;
	char	*cmd2;
	/*********/
}	t_cmd;

typedef struct s_data {
	char	**env;
	char	**export;
	int		error;
	int		exit_status;
	int		flag;
	int		tmpin;
	int		tmpout;
	int		number_of_commend;
	t_cmd	*cmd;
	t_list	*cmds;
}	t_data;

t_data	g_data;

int		parsing(char *line);
int		unclosed_quotes(char *line);
void	creat_env(char **env);
void	creat_export(char **env);
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

void	execution(void);

void	print_env(void);
void	print_export(void);
void	ft_export(void);
void	new_environment(void);
void	ft_set_env(char *name, char *value);
void	ft_set_export(char *name, char *value);
void	ft_unset(void);
char	**ft_remove_element(char **env, int n);


/*------------------------------EXECUTION----------------------------------*/

void	execution(void);
void	creat_env(char **env);
void	run_cmd(t_cmd *cmd);

/*------------------------------ERROR--------------------------------------*/

void	error(char *s, char *str, int status_code);
void	error3(char *s);
void	error2(int status_code);

/*------------------------EXECUTION_UTILS_FUNCTION-------------------------*/

char	**get_path(char **env);
void	*check_cmd(char **path, char *cmd);
void	free_path(char **paths);

/*------------------------------BUILTINS----------------------------------*/
void    ft_builtins(void);
int		is_builtins(void);
void    echo(void);
void	pwd(void);
void    cd(void);
void    unset(void);
void	ft_env(void);
void	ft_export(void);
void	ft_unset(void);
void    exit_cmd(void);
void	init_signal(void);

#endif