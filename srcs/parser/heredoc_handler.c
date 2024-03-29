/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 18:26:59 by omanar            #+#    #+#             */
/*   Updated: 2022/08/29 17:14:17 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*parse_limiter(char *str, int *expand)
{
	char	q;
	char	*new;
	char	*tmp;
	int		i;
	int		start;

	i = -1;
	new = ft_calloc(1, sizeof(char));
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			(*expand) = 0;
			start = i + 1;
			q = str[i];
			while (str[++(i)] && str[i] != q)
				;
			tmp = ft_substr(str, start, i - start);
		}
		else
			tmp = ft_substr(str, i, 1);
		new = advanced_join(new, tmp);
		free(tmp);
	}
	return (new);
}

char	*parse_buff(char *buff)
{
	int		i;
	char	*new;
	char	*tmp;

	i = -1;
	new = ft_calloc(1, sizeof(char));
	while (buff[++i])
	{
		if (buff[i] == '$')
			tmp = parse_dollar(buff, &i, 1);
		else
			tmp = ft_substr(buff, i, 1);
		new = advanced_join(new, tmp);
		free(tmp);
	}
	free (buff);
	return (new);
}

void	open_heredoc(char *value, int expand)
{
	char	*buff;

	if (pipe(g_data.cmd->end) == -1)
		perror("minishell: pipe");
	while (42)
	{
		buff = readline("> ");
		if (!buff)
			break ;
		if (!buff[0])
			ft_putstr_fd("\n", g_data.cmd->end[1]);
		else if (!ft_strncmp(buff, value,
				big_len(ft_strlen(value), ft_strlen(buff))))
			break ;
		if (expand == 1)
			buff = parse_buff(buff);
		ft_putstr_fd(buff, g_data.cmd->end[1]);
		ft_putstr_fd("\n", g_data.cmd->end[1]);
		free(buff);
	}
	free(buff);
	g_data.cmd->input = g_data.cmd->end[0];
	close(g_data.cmd->end[1]);
}

void	token_heredoc(t_lexer **lexer, t_token **token)
{
	int		expand;
	char	*value;

	g_data.signal_heredoc = 1;
	g_data.tmpin = dup(0);
	free_token(*token);
	*token = lexer_next_token(*lexer);
	expand = 1;
	value = parse_limiter((*token)->value, &expand);
	if (g_data.breaker == 0)
		open_heredoc(value, expand);
	free (value);
	dup2(g_data.tmpin, 0);
	close(g_data.tmpin);
	g_data.signal_heredoc = 0;
}
