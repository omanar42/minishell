
#include <minishell.h>

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_putendl_fd(g_data.newpwd, 1);
	else
		ft_putendl_fd(pwd, 1);
	free(pwd);
}
