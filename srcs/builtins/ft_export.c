/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:47:08 by omanar            #+#    #+#             */
/*   Updated: 2022/08/11 18:36:20 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_set_env(char *name, char *value)
{
	char	*tmp;

	tmp = ft_calloc(1, sizeof(char));
	tmp = advanced_join(tmp, name);
	tmp = advanced_join(tmp, "=");
	tmp = advanced_join(tmp, value);
	g_data.env = advanced_add(g_data.env, tmp);
	free(tmp);
}

void	ft_set_export(char *name, char *value)
{
	char	*tmp;

	tmp = ft_calloc(1, sizeof(char));
	tmp = advanced_join(tmp, "declare -x ");
	tmp = advanced_join(tmp, name);
	tmp = advanced_join(tmp, "=\"");
	tmp = advanced_join(tmp, value);
	tmp = advanced_join(tmp, "\"");
	g_data.export = advanced_add(g_data.export, tmp);
	free(tmp);
}

void	new_environment(void)
{
	int		i;
	char	*tmp;
	char	*name;
	char	*value;

	i = 0;
	while (((t_cmd *)(g_data.cmds->content))->args[++i])
	{
		tmp = ((t_cmd *)(g_data.cmds->content))->args[i];
		name = get_variable_name(((t_cmd *)(g_data.cmds->content))->args[i]);
		value = ft_strdup(tmp + get_char_index(tmp, '=') + 1);
		ft_set_env(name, value);
		ft_set_export(name, value);
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
