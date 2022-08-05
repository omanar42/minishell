/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:00:01 by omanar            #+#    #+#             */
/*   Updated: 2022/08/05 17:04:13 by omanar           ###   ########.fr       */
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

char	*advanced_join(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s2)
	{
		str = ft_strdup(s1);
		free(s1);
		return (str);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
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

char	*handle_spaces(char *value, char **new)
{
	int		i;
	char	*tmp;
	char	**strs;

	strs = ft_split(value, ' ');
	*new = advanced_join(*new, strs[0]);
	g_data.cmd->args = advanced_add(g_data.cmd->args, *new);
	i = 0;
	while (strs[++i + 1])
		g_data.cmd->args = advanced_add(g_data.cmd->args, strs[i]);
	tmp = ft_strdup(strs[i]);
	free(*new);
	*new = ft_calloc(1, sizeof(char));
	free(value);
	free_loop(strs);
	return (tmp);
}
