/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:58:20 by omanar            #+#    #+#             */
/*   Updated: 2022/07/27 23:28:35 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	hundle_word(t_token *token)
{
	// if (ft_strchr(token->value, '"'))
	// 	quotes_parsing(lexer, token);
	// else
	g_data.cmd->args = advanced_add(g_data.cmd->args, token->value);
}

void	hundle_pipe(void)
{
	g_data.cmd->cmd = ft_strdup(g_data.cmd->args[0]);
	ft_lstadd_back(&g_data.cmds, ft_lstnew((void *)g_data.cmd));
	cmd_init();
}

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

int	hundle_outfile(t_token *token)
{
	g_data.cmd->output = open(token->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (g_data.cmd->output == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(token->value);
		g_data.cmd->exit_status = errno;
		g_data.cmd->error = 1;
	}
	return (g_data.cmd->output);
}

int	hundle_appoutfile(t_token *token)
{
	g_data.cmd->output = open(token->value,
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (g_data.cmd->output == -1)
	{
		perror(token->value);
		g_data.cmd->exit_status = errno;
		g_data.cmd->error = 1;
	}
	return (g_data.cmd->output);
}

// void	handle_heredoc(t_token *token)
// {
// }

void	tokens_handler(t_lexer *lexer)
{
	t_token	*token;

	token = lexer_next_token(lexer);
	while (token->e_type != TOKEN_EOF)
	{
		if (token->e_type == TOKEN_WORD)
			hundle_word(token);
		else if (token->e_type == TOKEN_PIPE)
			hundle_pipe();
		else if (token->e_type == TOKEN_INFILE)
		{
			free_token(token);
			token = lexer_next_token(lexer);
			if (hundle_infile(token) == -1)
			{
				while (token->e_type != TOKEN_PIPE
					&& token->e_type != TOKEN_EOF)
				{
					free_token(token);
					token = lexer_next_token(lexer);
				}
				if (token->e_type == TOKEN_PIPE)
					hundle_pipe();
			}
		}
		else if (token->e_type == TOKEN_OUTFILE)
		{
			free_token(token);
			token = lexer_next_token(lexer);
			if (hundle_outfile(token) == -1)
			{
				while (token->e_type != TOKEN_PIPE
					&& token->e_type != TOKEN_EOF)
				{
					free_token(token);
					token = lexer_next_token(lexer);
				}
				if (token->e_type == TOKEN_PIPE)
					hundle_pipe();
			}
		}
		else if (token->e_type == TOKEN_APPOUT)
		{
			free_token(token);
			token = lexer_next_token(lexer);
			if (hundle_appoutfile(token) == -1)
			{
				while (token->e_type != TOKEN_PIPE
					&& token->e_type != TOKEN_EOF)
				{
					free_token(token);
					token = lexer_next_token(lexer);
				}
				if (token->e_type == TOKEN_PIPE)
					hundle_pipe();
			}
		}
		// else if (token->e_type == TOKEN_HEREDOC)
		// 	handle_heredoc(token);
		free_token(token);
		token = lexer_next_token(lexer);
	}
	g_data.cmd->cmd = ft_strdup(g_data.cmd->args[0]);
	ft_lstadd_back(&(g_data.cmds), ft_lstnew((void *)g_data.cmd));
	free_token(token);
}
