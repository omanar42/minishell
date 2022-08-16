/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiouane <adiouane@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:11:31 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/14 22:41:02 by adiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error(char *s, char *str, int status_code)
{
    printf("%s: %s\n", s, str);
	exit(status_code);
}

void	error1(char *s, int status_code)
{
    printf("%s\n", s);
	exit(status_code);
}

void	error2(int status_code)
{
	perror("minishell");
	exit(status_code);
}

void	error3(char *s)
{
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
}
