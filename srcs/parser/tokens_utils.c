/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:18:58 by omanar            #+#    #+#             */
/*   Updated: 2022/08/13 06:10:15 by adiouane         ###   ########.fr       */
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

int	open_infile(t_token *token)
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
	if (open_infile(*token) == -1)
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
