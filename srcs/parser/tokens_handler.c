/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:58:20 by omanar            #+#    #+#             */
/*   Updated: 2022/07/31 19:44:09 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// if (ft_strchr(token->value, '"'))
	// 	quotes_parsing(lexer, token);
	// else

int	token_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token->value, 2);
	ft_putstr_fd("'\n", 2);
	free_token(token);
	ft_lstadd_back(&(g_data.cmds), ft_lstnew((void *)g_data.cmd));
	return (1);
}

void	hundle_word(t_token *token)
{
	g_data.cmd->args = advanced_add(g_data.cmd->args, token->value);
}

void	hundle_pipe(void)
{
	g_data.cmd->cmd = ft_strdup(g_data.cmd->args[0]);
	ft_lstadd_back(&g_data.cmds, ft_lstnew((void *)g_data.cmd));
	cmd_init();
}

void	do_heredoc(t_lexer **lexer, t_token **token)
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
	g_data.cmd->heredoc = 1;
	g_data.cmd->input = g_data.cmd->end[0];
}

int	tokens_handler(t_lexer *lexer)
{
	t_token	*token;

	token = lexer_next_token(lexer);
	while (token->e_type != TOKEN_EOF)
	{
		if (token->e_type == TOKEN_ERROR)
			return (token_error(token));
		else if (token->e_type == TOKEN_WORD)
			hundle_word(token);
		else if (token->e_type == TOKEN_PIPE)
			hundle_pipe();
		else if (token->e_type == TOKEN_INFILE)
			token_infile(&lexer, &token);
		else if (token->e_type == TOKEN_OUTFILE)
			token_outfile(&lexer, &token);
		else if (token->e_type == TOKEN_APPOUT)
			token_appout(&lexer, &token);
		else if (token->e_type == TOKEN_HEREDOC)
			do_heredoc(&lexer, &token);
		free_token(token);
		token = lexer_next_token(lexer);
	}
	g_data.cmd->cmd = ft_strdup(g_data.cmd->args[0]);
	ft_lstadd_back(&(g_data.cmds), ft_lstnew((void *)g_data.cmd));
	free_token(token);
	return (0);
}
