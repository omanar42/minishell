/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 16:18:58 by omanar            #+#    #+#             */
/*   Updated: 2022/08/31 22:25:40 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	token_word(t_token **token)
{
	char	*value;

	value = parse_args((*token)->value);
	if (value[0] == '*' && (*token)->value[0] != '"'
		&& (*token)->value[0] != '\'')
		value = parse_star(value);
	if (value[0] != '\0' || !g_data.dollar)
		g_data.cmd->args = advanced_add(g_data.cmd->args, value);
	free(value);
}

char	*parse_dollar_redirection(char *str, int *i, int quote)
{
	int		start;
	char	*new;
	char	**tmp;

	start = *i + 1;
	g_data.dollar = 1;
	if (str[start] == '?')
	{
		new = ft_itoa(g_data.exit_status);
		(*i)++;
	}
	else if ((str[start] == '"' || str[start] == '\'') && !quote)
		return (NULL);
	else if (is_separator(str[start]) || !is_acceptable(str[start]))
		new = ft_strdup("$");
	else
	{
		while (str[*i] && is_acceptable(str[++(*i)]))
			;
		new = new_value(str, *i, start);
		(*i)--;
	}
	tmp = ft_split(new, ' ');
	if (argslen(tmp) == 2)
	{
		free(new);
		new = ft_strdup(tmp[0]);
		free_loop(tmp);
	}
	else if (new == NULL || argslen(tmp) != 2)
	{
		g_data.cmd->error = 2;
		*i = start - 1;
		return (ft_strdup("$"));
	}
	return (new);
}

char	*handle_spaces_redirection(char *value, char **new)
{
	int		i;
	char	*tmp;
	char	**strs;

	strs = ft_split(value, ' ');
	i = 0;
	*new = advanced_join(*new, strs[i++]);
	tmp = *new;
	while (strs[i])
		g_data.cmd->args = advanced_add(g_data.cmd->args, strs[i++]);
	// free(*new);
	*new = ft_calloc(1, sizeof(char));
	free(value);
	free_loop(strs);
	// printf("tmp: %s\n", tmp);
	return (tmp);
}

char	*parse_redirection(char *str)
{
	int		i;
	char	*new;
	char	*tmp;

	i = -1;
	new = ft_calloc(1, sizeof(char));
	while (str[++i])
	{
		if (str[i] == '"')
			tmp = parse_dquote(str, &i);
		else if (str[i] == '\'')
			tmp = parse_squote(str, &i);
		else if (str[i] == '$')
		{
			tmp = parse_dollar_redirection(str, &i, 0);
		}
		else
			tmp = ft_substr(str, i, 1);
		new = advanced_join(new, tmp);
		free(tmp);
	}
	return (new);
}

void	open_infile(t_token *token)
{
	char	*value;

	value = parse_redirection(token->value);
	if (g_data.cmd->error)
	{
		g_data.cmd->infile = ft_strdup(value);
		g_data.exit_status = 1;
		free(value);
		return ;
	}
	g_data.cmd->input = open(value, O_RDONLY);
	if (g_data.cmd->input == -1)
	{
		g_data.cmd->infile = ft_strdup(value);
		g_data.cmd->errno_value = errno;
		g_data.cmd->error = 1;
		g_data.exit_status = 1;
	}
	free(value);
}

int	token_error2(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token->value[0] == '\0' || token->value[0] == '\n')
		ft_putstr_fd("newline", 2);
	else
		ft_putstr_fd(token->value, 2);
	ft_putstr_fd("'\n", 2);
	g_data.exit_status = 258;
	ft_lstadd_back(&(g_data.cmds), ft_lstnew((void *)g_data.cmd));
	return (1);
}

void	token_infile(t_lexer **lexer, t_token **token)
{
	free_token(*token);
	*token = lexer_next_token(*lexer);
	if (g_data.cmd->input == -1)
		return ;
	open_infile(*token);
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
	value = parse_redirection((*token)->value);
	if (g_data.cmd->error)
	{
		g_data.cmd->infile = ft_strdup(value);
		g_data.exit_status = 1;
		free(value);
		return ;
	}
	g_data.cmd->outfiles = advanced_add(g_data.cmd->outfiles, value);
	g_data.cmd->append = set_new_append(g_data.cmd->append, i, append);
	free(value);
}
