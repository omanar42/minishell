/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:58:20 by omanar            #+#    #+#             */
/*   Updated: 2022/08/02 02:45:18 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	token_error(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token->value, 2);
	ft_putstr_fd("'\n", 2);
	ft_lstadd_back(&(g_data.cmds), ft_lstnew((void *)g_data.cmd));
	free_token(token);
	return (1);
}

// void	quotes_parsing(t_lexer **lexer, t_token **token)
// {
// 	int		i;
// 	int		dq;
// 	char	*str;

// 	i = 0;
// 	dq = 0;
// 	str = (*token)->value;
// 	while (str[i] && str[i] != '"')
// 		i++;
// 	while ()
// 	{
// 		if (str[i] == '"')
// 			dq++;
// 		else if (token->value[0] == '\'')
// 			dq = 2;
// 		if (lexer->c == '$')
// 	}
// }

	// if (ft_strchr((*token)->value, '"'))
	// 	quotes_parsing(lexer, token);
	// else

void	hundle_word(t_token **token)
{
	g_data.cmd->args = advanced_add(g_data.cmd->args, (*token)->value);
}

void	hundle_pipe(void)
{
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
	if (token->e_type == TOKEN_PIPE)
		return (token_error(token));
	while (token->e_type != TOKEN_EOF)
	{
		if (token->e_type == TOKEN_ERROR)
			return (token_error(token));
		else if (token->e_type == TOKEN_WORD)
			hundle_word(&token);
		else if (token->e_type == TOKEN_INFILE)
			token_infile(&lexer, &token);
		else if (token->e_type == TOKEN_OUT || token->e_type == TOKEN_APP)
			token_outfile(&lexer, &token);
		else if (token->e_type == TOKEN_HEREDOC)
			do_heredoc(&lexer, &token);
		else if (token->e_type == TOKEN_PIPE)
			hundle_pipe();
		free_token(token);
		token = lexer_next_token(lexer);
	}
	ft_lstadd_back(&(g_data.cmds), ft_lstnew((void *)g_data.cmd));
	free_token(token);
	return (0);
}
