/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:22:40 by omanar            #+#    #+#             */
/*   Updated: 2022/08/29 17:25:15 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_export(char *name)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	g_data.exit_status = 1;
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

char	*make_line(char *name, char *value)
{
	char	*tmp;

	tmp = ft_calloc(1, sizeof(char));
	tmp = advanced_join(tmp, name);
	tmp = advanced_join(tmp, "=");
	tmp = advanced_join(tmp, value);
	return (tmp);
}
