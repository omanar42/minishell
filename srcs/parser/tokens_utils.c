/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:18:58 by omanar            #+#    #+#             */
/*   Updated: 2022/08/21 04:59:05 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_word(t_token **token)
{
	char	*value;

	value = parse_args((*token)->value);
	if (value[0] != '\0' || !g_data.dollar)
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
		g_data.exit_status = 1;
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
		if ((*token)->e_type == TOKEN_PIPE)
			token_pipe();
	}
}

int	*set_new_append(int *tab, int i, int value)
{
	int	*new;
	int	j;

	j = -1;
	new = ft_calloc(i + 1, sizeof(int));
	while (++j < i)
		new[j] = tab[j];
	new[i] = value;
	free(tab);
	return (new);
}

void	token_outfile(t_lexer **lexer, t_token **token, int i)
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
	g_data.cmd->append = set_new_append(g_data.cmd->append, i, append);
	free(value);
}
