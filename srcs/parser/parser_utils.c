/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:00:01 by omanar            #+#    #+#             */
/*   Updated: 2022/08/02 20:30:15 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	argslen(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i + 1);
}

char	**advanced_add(char **strs, char *arg)
{
	char	**args;
	int		wlen;
	int		i;

	if (!strs[0] || !strs)
	{
		args = (char **)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(arg);
		args[1] = NULL;
		free_loop(strs);
		return (args);
	}
	wlen = argslen(strs);
	args = (char **)malloc(sizeof(char *) * (wlen + 1));
	i = 0;
	while (strs[i])
	{
		args[i] = ft_strdup(strs[i]);
		i++;
	}
	args[i] = ft_strdup(arg);
	args[i + 1] = NULL;
	free_loop(strs);
	return (args);
}

int	unclosed_quotes(char *line)
{
	int	i;
	int	sign;

	i = -1;
	sign = 0;
	while (line[++i])
	{
		if (line[i] == '\'')
			if (sign != 2)
				sign = (((sign == 0) * 1) + ((sign == 1) * 0));
		if (line[i] == '"')
			if (sign != 1)
				sign = (((sign == 0) * 2) + ((sign == 2) * 0));
	}
	return (sign);
}

char	*expand_dollar(char *str, char **env)
{
	int		i;
	char	*new;
	char	*tmp;

	i = -1;
	while (env[++i])
	{
		tmp = ft_strnstr(env[i], str, ft_strlen(str));
		if (tmp)
		{
			new = ft_substr(tmp, ft_strlen(str) + 1, ft_strlen(tmp));
			return (new);
		}
	}
	return (NULL);
}
