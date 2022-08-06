/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 01:11:15 by omanar            #+#    #+#             */
/*   Updated: 2022/08/06 17:42:46 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_acceptable(char c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == '_')
		return (1);
	return (0);
}

int	is_separator(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r' || c == '\0')
		return (1);
	return (0);
}

char	*parse_dollar_brace(char *str, int *i)
{
	int j;
	int		start;
	char	*new;
	char	*tmp;

	start = *i + 1;
	j = 0;
	while (str[*i] && str[*i] != '}')
			(*i)++;
	tmp = ft_substr(str, start, *i - start);
	new = parse_dollar(tmp, &j);
	free(tmp);
	return (new);
}

char	*parse_dollar(char *str, int *i)
{
	int		start;
	char	*new;
	char	*tmp;

	start = *i + 1;
	if (is_separator(str[1]))
		return (ft_strdup("$"));
	else if (str[1] == '?')
		new = ft_itoa(g_data.exit_status);
	else if (str[1] == '{')
		new = parse_dollar_brace(str, i);
	else
	{
		printf("i = %d\n", *i);
		while (str[*i] && is_acceptable(str[++(*i)]))
			;
		tmp = ft_substr(str, start, *i - start);
		if (!tmp[0])
			return (NULL);
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
