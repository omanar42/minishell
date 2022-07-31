/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:18:58 by omanar            #+#    #+#             */
/*   Updated: 2022/07/31 17:03:31 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	hundle_infile(t_token *token)
{
	g_data.cmd->input = open(token->value, O_RDONLY);
	if (g_data.cmd->input == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(token->value);
		g_data.cmd->exit_status = errno;
		g_data.cmd->error = 1;
	}
	return (g_data.cmd->input);
}

int	hundle_outfile(t_token *token, int app)
{
	if (app)
		g_data.cmd->output = open(token->value,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		g_data.cmd->output = open(token->value,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (g_data.cmd->output == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(token->value);
		g_data.cmd->exit_status = errno;
		g_data.cmd->error = 1;
	}
	return (g_data.cmd->output);
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
		}
		if ((*token)->e_type == TOKEN_PIPE)
			hundle_pipe();
	}
}

void	token_outfile(t_lexer **lexer, t_token **token)
{
	free_token(*token);
	*token = lexer_next_token(*lexer);
	if (hundle_outfile(*token, 0) == -1)
	{
		while ((*token)->e_type != TOKEN_PIPE
			&& (*token)->e_type != TOKEN_EOF)
		{
			free_token(*token);
			*token = lexer_next_token(*lexer);
		}
		if ((*token)->e_type == TOKEN_PIPE)
			hundle_pipe();
	}
}

void	token_appout(t_lexer **lexer, t_token **token)
{
	free_token(*token);
	*token = lexer_next_token(*lexer);
	if (hundle_outfile(*token, 1) == -1)
	{
		while ((*token)->e_type != TOKEN_PIPE
			&& (*token)->e_type != TOKEN_EOF)
		{
			free_token(*token);
			*token = lexer_next_token(*lexer);
		}
		if ((*token)->e_type == TOKEN_PIPE)
			hundle_pipe();
	}
}
