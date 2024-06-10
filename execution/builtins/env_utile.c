#include "../../minishell.h"
t_env	*ft_lstnew_env(char *line)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->content = line;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (!*lst || !lst)
	{
		*lst = new;
		return;
	}
	if (!new) 
		return;
	ptr = *lst;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
}


t_env	*get_env(char **env)
{
	int	i;
	t_env	*line;
	t_env	*env_list;
	
	env_list = NULL;
	i = 0;
	while (env[i])
	{
		line = ft_lstnew_env(env[i]);
		ft_lstadd_back_env(&env_list, line);
		// ft_putstr_fd(env[i], 1);
		i++;
	}
	return (env_list);
}
