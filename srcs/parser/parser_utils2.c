/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 01:11:15 by omanar            #+#    #+#             */
/*   Updated: 2022/08/06 23:10:07 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*parse_dollar(char *str, int *i)
{
	int		start;
	char	*new;
	char	*tmp;

	start = *i + 1;
	if (is_separator(str[start]) || !is_acceptable(str[start]))
		new = ft_strdup("$");
	else if (str[start] == '?')
		new = ft_itoa(g_data.exit_status);
	else
	{
		while (str[*i] && is_acceptable(str[++(*i)]))
			;
		tmp = ft_substr(str, start, *i - start);
		if (!tmp[0])
		{
			free(tmp);
			return (NULL);
		}
		else
			new = expand_dollar(tmp, g_data.env);
		free(tmp);
		(*i)--;
	}
	return (new);
}

char	*parse_dquotes(char *str, int *i)
{
	char	*new;
	char	*tmp;

	new = ft_calloc(1, sizeof(char));
	while (str[++(*i)] && str[*i] != '"')
	{
		if (str[*i] == '$')
			tmp = parse_dollar(str, i);
		else
			tmp = ft_substr(str, *i, 1);
		new = advanced_join(new, tmp);
		free(tmp);
	}
	return (new);
}

char	*parse_squotes(char *str, int *i)
{
	int		start;
	char	*new;

	start = *i + 1;
	while (str[++(*i)] && str[*i] != '\'')
		;
	new = ft_substr(str, start, *i - start);
	return (new);
}

char	*arg_parsing(char *str)
{
	int		i;
	char	*new;
	char	*tmp;

	i = -1;
	new = ft_calloc(1, sizeof(char));
	while (str[++i])
	{
		if (str[i] == '"')
			tmp = parse_dquotes(str, &i);
		else if (str[i] == '\'')
			tmp = parse_squotes(str, &i);
		else if (str[i] == '$')
		{
			tmp = parse_dollar(str, &i);
			if (ft_strchr(tmp, ' '))
				tmp = handle_spaces(tmp, &new);
		}
		else
			tmp = ft_substr(str, i, 1);
		new = advanced_join(new, tmp);
		free(tmp);
	}
	return (new);
}
