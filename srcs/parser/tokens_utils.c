/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:18:58 by omanar            #+#    #+#             */
/*   Updated: 2022/08/08 23:03:29 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_word(t_token **token)
{
	char	*value;

	value = parse_args((*token)->value);
	g_data.cmd->args = advanced_add(g_data.cmd->args, value);
	free(value);
}

int	hundle_infile(t_token *token)
{
	char	*value;

	value = parse_args(token->value);
	g_data.cmd->input = open(value, O_RDONLY);
	if (g_data.cmd->input == -1)
	{
		g_data.cmd->infile = ft_strdup(value);
		g_data.cmd->exit_status = errno;
		g_data.cmd->error = 1;
	}
	free(value);
	return (g_data.cmd->input);
}

void	token_infile(t_lexer **lexer, t_token **token)
{
	free_token(*token);
	*token = lexer_next_token(*lexer);
	if (hundle_infile(*token) == -1)
	{
		while ((*token)->e_type != TOKEN_PIPE
			&& (*token)->e_type != TOKEN_EOF)
		{
			free_token(*token);
			*token = lexer_next_token(*lexer);
			if ((*token)->e_type == TOKEN_HEREDOC)
				token_heredoc(lexer, token);
		}
		if (g_data.cmd->error == 1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(g_data.cmd->infile, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(g_data.cmd->exit_status), 2);
			ft_putstr_fd("\n", 2);
		}
		if ((*token)->e_type == TOKEN_PIPE)
			token_pipe();
	}
}

void	token_outfile(t_lexer **lexer, t_token **token)
{
	int		append;
	char	*value;

	append = 0;
	if ((*token)->e_type == TOKEN_APP)
		append = 1;
	free_token(*token);
	*token = lexer_next_token(*lexer);
	value = parse_args((*token)->value);
	g_data.cmd->outfiles = advanced_add(g_data.cmd->outfiles, value);
	free(value);
	g_data.cmd->append = append;
}

void	token_heredoc(t_lexer **lexer, t_token **token)
{
	char	*buff;

	free_token(*token);
	*token = lexer_next_token(*lexer);
	if (pipe(g_data.cmd->end) == -1)
		perror("minishell: pipe");
	while (42)
	{
		buff = readline("> ");
		if (!ft_strncmp(buff, (*token)->value, ft_strlen(buff)))
		{
			free(buff);
			break ;
		}
		ft_putstr_fd(buff, g_data.cmd->end[1]);
		free(buff);
	}
	g_data.cmd->input = g_data.cmd->end[0];
}
