/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omanar <omanar@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 23:11:31 by adiouane          #+#    #+#             */
/*   Updated: 2022/08/22 02:57:12 by omanar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_command_not_found(char *s, char *str, int status_code)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	exit(status_code);
}

void	exit_strerr(char *str, int err, int exit_status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(err), 2);
	exit(exit_status);
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
