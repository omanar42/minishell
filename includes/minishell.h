/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:20:55 by omanar            #+#    #+#             */
/*   Updated: 2022/08/29 22:43:55 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <lexer.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
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
	int		errno_value;
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
	int		stop;
	int		signalchild;
	int		signalqiut;
	int		signal_heredoc;
	int		breaker;
	char	*savepwd;
	int		test;
	int		dollar;
	int		fialdfork;
	char	*newpwd;
	int		p[2];
	pid_t	pid;
	int		status;
	int		cmds_size;
	int		last_fd;
	t_list	*tmp;
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
char	*parse_dollar(char *str, int *i, int quote);
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
int		big_len(int s1, int s2);

/*------------------------------EXECUTION----------------------------------*/

void	ft_child_process(t_cmd *cmd, int i, int last_fd);
void	execution(void);
void	creat_env(char **env);
void	run_cmd(t_cmd *cmd);

/*------------------------------ERROR--------------------------------------*/

void	error_command_not_found(char *s, char *str, int status_code);
void	exit_strerr(char *str, int err, int exit_status);
void	error_msg(char *str, int err);
void	error_infile(void);

/*------------------------EXECUTION_UTILS_FUNCTION-------------------------*/

char	**get_path(char **env);
void	*check_cmd(char **path, char *cmd);
void	free_path(char **paths);
void	redirect_input(void);
void	redirect_output(void);
void	open_outputs(void);
void	ft_dup(int olfd, int nfd);
void	failed_fork(void);
void	waiting(int i, int status, int pid);
void	next_cmd(int last_fd);

/*------------------------------BUILTINS----------------------------------*/

void	ft_builtins(void);
int		is_builtins(void);
int		is_builtins_in_child(void);
void	ft_builtins_in_child(void);
void	echo(void);
void	pwd(void);
void	cd(void);
void	ft_env(void);
void	*ft_getenv(char *str);
void	exit_cmd(void);
char	*make_line(char *name, char *value);
char	*get_name(char *str);
void	error_export(char *name);

/*----------------------------SIGNALS--------------------------------------*/
void	handlear(int signal);
void	init_signal(void);

/*----------------------------WILDCARD--------------------------------------*/
char	*get_list(void);
DIR		*addvanced_opendir(void);
char	*parse_star(char *str);

#endif