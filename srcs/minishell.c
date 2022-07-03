/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:34:41 by omanar            #+#    #+#             */
/*   Updated: 2022/07/03 21:16:48 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_cmds(char *line)
{
	int	i;
	int	nb_cmd;

	i = 0;
	nb_cmd = 1;
	while (line[i])
	{
		if ((line[i] == '|' && line[i + 1] == '|')
			&& (line[i] == '&' && line[i + 1] == '&'))
		{
			i++;
			nb_cmd++;
		}
		if (line[i] == '|')
			nb_cmd++;
		i++;
	}
	return (nb_cmd);
}

void	data_init(char *line)
{
	int	i;

	i = 0;
	g_data.nb_cmd = get_cmds(line);
	g_data.cmd = (t_cmd *)malloc(sizeof(t_cmd) * g_data.nb_cmd);
	g_data.index = 0;
	while (i < g_data.nb_cmd)
	{
		g_data.cmd[i].cmd = NULL;
		g_data.cmd[i].path = NULL;
		g_data.cmd[i].args = NULL;
		g_data.cmd[i].input = NULL;
		g_data.cmd[i].output = NULL;
		g_data.cmd[i].appand = 0;
		g_data.cmd[i].heredoc = 0;
		g_data.cmd[i].status = 0;
		i++;
	}
}

void	ft_free(t_token *token)
{
	free(token->value);
	free(token);
}

void	parsing(char *line, char **env)
{
	t_token	*token;
	t_lexer	*lexer;

	data_init(line);
	(void)env;
	lexer = lexer_init(line);
	token = lexer_next_token(lexer);
	while (token->e_type != TOKEN_EOF)
	{
		printf("TOK(%s) (%d)\n", token->value, token->e_type);
		ft_free(token);
		token = lexer_next_token(lexer);
	}
	ft_free(token);
	free(lexer);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)av;
	if (ac != 1)
		return (0);
	while (42)
	{
		line = readline(GRN "➜ " CYN " minishell$ " RST);
		if (!line)
			continue ;
		add_history(line);
		parsing(line, env);
		free(line);
	}
	return (0);
}
