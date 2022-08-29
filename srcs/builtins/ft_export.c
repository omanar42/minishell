/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:47:08 by omanar            #+#    #+#             */
/*   Updated: 2022/08/29 17:25:05 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
					big_len(get_index(g_data.export[j], '='),
						get_index(tmp, '='))))
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

void	ft_set_env(char *name, char *value)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = -1;
	if (!value)
		return ;
	tmp = make_line(name, value);
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
