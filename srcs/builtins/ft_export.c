/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:47:08 by omanar            #+#    #+#             */
/*   Updated: 2022/08/17 03:05:19 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_new_line(char *name, char *value)
{
	char	*tmp;

	tmp = ft_calloc(1, sizeof(char));
	tmp = advanced_join(tmp, "declare -x ");
	tmp = advanced_join(tmp, name);
	if (value)
	{
		tmp = advanced_join(tmp, "=\"");
		tmp = advanced_join(tmp, value);
		tmp = advanced_join(tmp, "\"");
	}
	return (tmp);
}

void	ft_set_export(char *name, char *value, int exist)
{
	int		j;
	char	*tmp;

	j = -1;
	tmp = get_new_line(name, value);
	if (exist)
	{
		while (value && g_data.export[++j])
		{
			if (!ft_strncmp(g_data.export[j], tmp,
					get_char_index(g_data.export[j], '=')))
			{
				free(g_data.export[j]);
				g_data.export[j] = ft_strdup(tmp);
				free(tmp);
				return ;
			}
		}
	}
	else
		g_data.export = advanced_add(g_data.export, tmp);
	free(tmp);
}

int	get_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (i);
}

char	*get_name(char *str)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = malloc(sizeof(char) * get_index(str, '=') + 1);
	if (!tmp)
		return (NULL);
	while (++i < get_index(str, '='))
		tmp[i] = str[i];
	tmp[i] = 0;
	return (tmp);
}

void	error_export(char *name)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_data.exit_status = 1;
}

int	big_len(int s1, int s2)
{
	if (s1 > s2)
		return (s1);
	return (s2);
}

void	ft_set_env(char *name, char *value)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = -1;
	if (!value)
		return ;
	tmp = ft_calloc(1, sizeof(char));
	tmp = advanced_join(tmp, name);
	tmp = advanced_join(tmp, "=");
	tmp = advanced_join(tmp, value);
	while (g_data.env[++i])
	{
		tmp2 = get_variable_name(g_data.env[i]);
		if (!ft_strncmp(tmp2, name, big_len(ft_strlen(tmp2), ft_strlen(name))))
		{
			free(g_data.env[i]);
			g_data.env[i] = ft_strdup(tmp);
			free(tmp);
			free(tmp2);
			return ;
		}
		free(tmp2);
	}
	g_data.env = advanced_add(g_data.env, tmp);
	free(tmp);
}

int	is_variable_exist(char *name)
{
	int		i;
	char	*tmp;

	tmp = get_new_line(name, NULL);
	i = -1;
	while (g_data.export[++i])
	{
		if (ft_strncmp(g_data.export[i], tmp,
				big_len(get_index(g_data.export[i], '='), ft_strlen(tmp))) == 0)
		{
			free(tmp);
			return (i);
		}
	}
	free(tmp);
	return (-1);
}

int	check_error(char *arg)
{
	int	i;

	if (ft_isdigit(arg[0]))
		return (1);
	i = -1;
	while (arg[++i])
		if (!is_acceptable(arg[i]))
			return (1);
	return (0);
}

void	new_environment(void)
{
	int		i;
	char	**tmp;
	char	*name;
	char	*value;

	i = 0;
	tmp = ((t_cmd *)(g_data.cmds->content))->args;
	while (tmp[++i])
	{
		value = NULL;
		name = get_name(tmp[i]);
		if ((!name || !name[0]) || check_error(name))
		{
			(error_export(tmp[i]), free(name));
			continue ;
		}
		if (ft_strchr(tmp[i], '='))
			value = ft_strdup(tmp[i] + get_char_index(tmp[i], '=') + 1);
		if (is_variable_exist(name) != -1)
			(ft_set_env(name, value), ft_set_export(name, value, 1));
		else
			(ft_set_env(name, value), ft_set_export(name, value, 0));
		free(name);
		free(value);
	}
}

void	ft_export(void)
{
	int		len;

	len = argslen(((t_cmd *)(g_data.cmds->content))->args);
	if (len == 2)
		print_export();
	else
		new_environment();
}
