/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:18:58 by omanar            #+#    #+#             */
/*   Updated: 2022/08/07 15:41:57 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_word(t_token **token)
{
	char	*value;

	value = arg_parsing((*token)->value);
	g_data.cmd->args = advanced_add(g_data.cmd->args, value);
	free(value);
}

void	token_infile(t_lexer **lexer, t_token **token)
{
	char	*value;

	free_token(*token);
	*token = lexer_next_token(*lexer);
	value = arg_parsing((*token)->value);
	g_data.cmd->infiles = advanced_add(g_data.cmd->infiles, value);
	free(value);
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
	value = arg_parsing((*token)->value);
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
	g_data.cmd->heredoc = 1;
	g_data.cmd->input = g_data.cmd->end[0];
}

void	token_pipe(void)
{
	ft_lstadd_back(&g_data.cmds, ft_lstnew((void *)g_data.cmd));
	cmd_init();
}
