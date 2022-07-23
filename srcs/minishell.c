/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 17:34:41 by omanar            #+#    #+#             */
/*   Updated: 2022/07/23 18:37:08 by omanar           ###   ########.fr       */
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

void	ft_free(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_cmd(void)
{
	int	i;

	i = 0;
	while (i < g_data.nb_cmd)
	{
		free(g_data.cmd[i].path);
		ft_free(g_data.cmd[i].args);
		free(g_data.cmd[i].input);
		free(g_data.cmd[i].output);
		i++;
	}
	free(g_data.cmd);
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
		g_data.cmd[i].args = (char **)malloc(sizeof(char *));
		g_data.cmd[i].args[0] = NULL;
		g_data.cmd[i].input = NULL;
		g_data.cmd[i].output = NULL;
		g_data.cmd[i].appand = 0;
		g_data.cmd[i].heredoc = 0;
		g_data.cmd[i].status = 0;
		i++;
	}
}

void	dollar_parsing(t_lexer *lexer, t_token *token)
{
	(void)lexer;
	(void)token;
}

void	quotes_parsing(t_lexer *lexer, t_token *token)
{
	int		i;
	char	**args;

	i = 0;
	if (ft_strchr(token->value, '$'))
		dollar_parsing(lexer, token);
	else
	{
		args = ft_split(token->value, '"');
		while (args[i])
		{
			if (args[i][0] == '$')
				dollar_parsing(lexer, token);
			if (i == 0)
				((t_cmd *)(g_data.cmds->content))->cmd = args[i];
			else
				((t_cmd *)(g_data.cmds->content))->args[i] = args[i];
			i++;
		}
	}
}

int	argslen(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i + 1);
}

char	**advanced_add(char **strs, char *arg)
{
	char	**args;
	int		wlen;
	int		i;
	
	if (!strs[0] || !strs)
	{
		args = (char **)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(arg);
		args[1] = NULL;
		ft_free(strs);
		return (args);
	}
	wlen = argslen(strs);
	args = (char **)malloc(sizeof(char *) * (wlen + 1));
	i = 0;
	while (strs[i])
	{
		args[i] = ft_strdup(strs[i]);
		i++;
	}
	args[i] = ft_strdup(arg);
	args[i + 1] = NULL;
	ft_free(strs);
	return (args);
}

void	hundle_word(t_lexer *lexer, t_token *token)
{
	(void)lexer;
	// if (ft_strchr(token->value, '"'))
	// 	quotes_parsing(lexer, token);
	// else
		g_data.cmd->args = advanced_add(g_data.cmd->args, token->value);
}

void	init_cmd(t_lexer *lexer, t_token *token)
{
	if (token->e_type == TOKEN_WORD)
		hundle_word(lexer, token);
	g_data.cmd->cmd = g_data.cmd->args[0];
}

void	parser(t_lexer *lexer)
{
	t_token	*token;

	token = lexer_next_token(lexer);
	while (token->e_type != TOKEN_EOF)
	{
		init_cmd(lexer, token);
		free_token(token);
		token = lexer_next_token(lexer);
	}
	// printf("cmd = %s\n", g_data.cmd->cmd);
	// int i = -1;
	// while (g_data.cmd->args[++i])
	// 	printf("arg[%d] = %s\n", i, g_data.cmd->args[i]);
	// g_data.cmds->content = (void *) cmd;
	// if (token->e_type == TOKEN_WORD)
	// 	hundle_word(lexer, token);
	free_token(token);
}

void	parsing(char *line, char **env)
{
	t_lexer	*lexer;

	data_init(line);
	(void)env;
	lexer = lexer_init(line);
	parser(lexer);
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
		free_cmd();
		free(line);
		system("leaks -q minishell");
	}
	return (0);
}
