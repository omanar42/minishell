/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:18:58 by omanar            #+#    #+#             */
/*   Updated: 2022/08/01 00:19:38 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_infile(t_lexer **lexer, t_token **token)
{
	free_token(*token);
	*token = lexer_next_token(*lexer);
	g_data.cmd->infiles = advanced_add(g_data.cmd->infiles, (*token)->value);
}

void	token_outfile(t_lexer **lexer, t_token **token)
{
	int	append;

	append = 0;
	if ((*token)->e_type == TOKEN_APP)
		append = 1;
	free_token(*token);
	*token = lexer_next_token(*lexer);
	g_data.cmd->outfiles = advanced_add(g_data.cmd->outfiles, (*token)->value);
	g_data.cmd->append = append;
}
