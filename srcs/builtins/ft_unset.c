/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 17:39:40 by omanar            #+#    #+#             */
/*   Updated: 2022/08/15 15:21:46 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_remove_element(char **env, int n)
{
	int		i;
	int		j;
	char	**new;

	i = -1;
	j = -1;
	new = (char **)malloc(sizeof(char *) * (argslen(env) - 1));
	while (env[++i])
		if (i != n)
			new[++j] = ft_strdup(env[i]);
	new[j] = NULL;
	free_loop(env);
	return (new);
}

void	ft_unset(void)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (g_data.env[++i])
	{
		tmp = get_variable_name(g_data.env[i]);
		j = 0;
		while (((t_cmd *)(g_data.cmds->content))->args[++j])
		{
			if (!ft_strncmp(tmp, ((t_cmd *)(g_data.cmds->content))->args[j],
				ft_strlen(tmp)))
			{
				g_data.env = ft_remove_element(g_data.env, i);
				g_data.export = ft_remove_element(g_data.export, i);
				i--;
				break ;
			}
		}
	}
}
