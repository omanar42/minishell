/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:20:55 by omanar            #+#    #+#             */
/*   Updated: 2022/08/21 22:11:06 by omanar           ###   ########.fr       */
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
# include <dirent.h>

# define RST "\033[0m"
# define RED "\033[0;31m"
# define GRN "\033[0;32m"
# define CYN "\033[0;36m"

typedef struct s_outfiles
{
	int		app;
	char	*value;
}	t_outfiles;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	int		end[2];
	int		input;
	char	*infile;
	int		output;
	char	**outfiles;
	int		*append;
	int		app_index;
	int		error;
	int		exit_status;
	pid_t	pid;
	int		fd_p[2];
	char	**paths;
}	t_cmd;

typedef struct s_data {
	char	**env;
	char	**export;
	int		error;
	int		exit_status;
	int		flag;
	int		tmpin;
	int		tmpout;
	int		signalchild;
	int		signalqiut;
	int		signal_heredoc;
	int		breaker;
	char	*savepwd;
	int		test;
	int		dollar;
	char	*newpwd;
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
void	token_outfile(t_lexer **lexer, t_token **token, int i);
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
void	ft_set_export(char *name, char *value, int exist);
void	ft_unset(void);
char	**ft_remove_element(char **env, int n);
int		is_variable_exist(char *name);
int		get_index(char *str, char c);
char	*get_new_line(char *name, char *value);
int		check_error(char *arg);
int		check_path(char **env);

/*------------------------------EXECUTION----------------------------------*/

void	execution(void);
void	creat_env(char **env);
void	run_cmd(t_cmd *cmd);

/*------------------------------ERROR--------------------------------------*/

void	error_command_not_found(char *s, char *str, int status_code);
void	error1(char *s, int status_code);
void	error2(int status_code);
void	error3(char *s);
void	exit_strerr(char *str, int err);

/*------------------------EXECUTION_UTILS_FUNCTION-------------------------*/

char	**get_path(char **env);
void	*check_cmd(char **path, char *cmd);
void	free_path(char **paths);
void	redirect_input(void);
void	open_outputs(void);

/*------------------------------BUILTINS----------------------------------*/
void	ft_builtins(void);
int		is_builtins(void);
int		is_builtins_in_child(void);
void	ft_builtins_in_child(void);
void	echo(void);
void	pwd(void);
void	cd(void);
void	ft_env(void);
void	exit_cmd(void);

/*----------------------------SIGNALS--------------------------------------*/
void	handlear(int signal);
void	init_signal(void);

#endif