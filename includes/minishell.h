/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 17:20:55 by omanar            #+#    #+#             */
/*   Updated: 2022/07/25 15:57:37 by omanar           ###   ########.fr       */
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
	char	*input;
	char	*output;
	int		appand;
	int		heredoc;
	int		end[2];
	int		status;
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
	t_list	*infiles;
	t_list	*outfiles;
	t_list	*limiters;
}	t_data;

t_data	g_data;

void	parsing(char *line, char **env);
void	data_init(char *line);
int		get_cmds(char *line);
void	printer(void);
void	ft_free(char **args);
void	free_cmd(void *cmd);

#endif