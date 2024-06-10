#include "../../minishell.h"

void	ft_putstr_fd_special(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		if (fd >= 0)
		{
			write(fd, &s[i], 1);
			i++;
		}
	}
}

void	write_env(t_env *env)
{
	while(env)
	{
		if (ft_strchr(env->content, '='))
		{
			ft_putstr_fd(env->content, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
}