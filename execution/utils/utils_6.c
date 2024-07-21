#include "../../minishell.h"

char	**change_list_to_env(t_env *list_env)
{
	char	**env;
	int		i;

	i = 0;
	env = my_alloc(1024, 'a');
	while (list_env)
	{
		env[i] = list_env->content;
		i++;
		list_env = list_env->next;
	}
	env[i] = NULL;
	return (env);
}

int	ft_strlen_1(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		i++;
	return (i);
}



