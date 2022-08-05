/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:59:27 by omanar            #+#    #+#             */
/*   Updated: 2022/08/05 17:03:42 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

int	parsing(char *line)
{
	t_lexer	*lexer;

	if (unclosed_quotes(line))
	{
		ft_putstr_fd("minishell: syntax error unclosed quotes\n", 2);
		return (1);
	}
	data_init(line);
	lexer = lexer_init(line);
	if (tokens_handler(lexer))
	{
		free(lexer);
		return (1);
	}
	free(lexer);
	return (0);
}
