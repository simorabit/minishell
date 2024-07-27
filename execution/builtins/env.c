/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:44:57 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/27 02:51:39 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_emergency_env(t_env **env)
{
	t_env	*first_line;
	t_env	*second_line;
	t_env	*third_line;
	t_env	*path;
	char	*ptr;

	ptr = ft_strjoin("PATH=/Users/souaouri/.brew/bin:", NULL);
	ptr = ft_strjoin(ptr, "/usr/local/bin:/usr/bin:/bin");
	path = ft_lstnew_env(ptr);
	first_line = ft_lstnew_env("PWD=/Users/souaouri/Desktop/mn_sh");
	second_line = ft_lstnew_env("SHLVL=1");
	third_line = ft_lstnew_env("_=/usr/bin/env");
	ft_lstadd_back_env(env, first_line);
	ft_lstadd_back_env(env, second_line);
	ft_lstadd_back_env(env, third_line);
	ft_lstadd_back_env(env, path);
}

void	env_print_error(char *arg, int i)
{
	if (i == 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void	write_env(t_env *env, char **arg)
{
	int		i;
	int		size;

	size = ft_lstsize_env(env);
	i = 1;
	if (size == 5)
		size--;
	while (arg[i])
	{
		if (!ft_strchr(arg[i], '='))
			return (env_print_error(arg[i], 1));
		i++;
	}
	while (env && size--)
	{
		if (ft_strchr(env->content, '=') && ft_strncmp(env->content, "?", 1))
		{
			ft_putstr_fd(env->content, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	i = 1;
	while (arg[i])
	{
		if (ft_strchr(arg[i], '='))
		{
			if (ft_strlen(arg[i]) == 1)
				env_print_error(arg[i], 2);
			ft_putstr_fd(arg[i], 1);
			ft_putstr_fd("\n", 1);
		}
		i++;
	}
}
