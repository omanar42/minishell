/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 01:11:15 by omanar            #+#    #+#             */
/*   Updated: 2022/08/05 01:12:35 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_acceptable(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

char	*parse_dollar(char *str, int *i)
{
	int		start;
	char	*new;
	char	*tmp;

	start = *i + 1;
	while (str[*i] && is_acceptable(str[++(*i)]))
		;
	tmp = ft_substr(str, start, *i - start);
	new = expand_dollar(tmp, g_data.env);
	free(tmp);
	(*i)--;
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

	i = 0;
	new = ft_calloc(1, sizeof(char));
	while (str[i])
	{
		if (str[i] == '"')
			tmp = parse_dquotes(str, &i);
		else if (str[i] == '\'')
			tmp = parse_squotes(str, &i);
		else if (str[i] == '$')
			tmp = parse_dollar(str, &i);
		else
			tmp = ft_substr(str, i, 1);
		new = advanced_join(new, tmp);
		free(tmp);
		i++;
	}
	return (new);
}
