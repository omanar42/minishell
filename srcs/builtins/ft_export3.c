/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 17:24:41 by omanar            #+#    #+#             */
/*   Updated: 2022/08/29 17:25:21 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	big_len(int s1, int s2)
{
	if (s1 > s2)
		return (s1);
	return (s2);
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
