/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:44:57 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/06 13:17:24 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	add_emergency_env(t_env **env)
{
	t_env	*first_line;
	t_env	*second_line;
	t_env	*third_line;
	t_env	*path;

	path = ft_lstnew_env("PATH=/Users/souaouri/.brew/bin:/usr/local/bin:/usr/bin:/bin");
	first_line = ft_lstnew_env("PWD=/Users/souaouri/Desktop/mn_sh");
	second_line = ft_lstnew_env("SHLVL=1");
	third_line = ft_lstnew_env("_=/usr/bin/env");
	ft_lstadd_back_env(env, path);
	ft_lstadd_back_env(env, first_line);
	ft_lstadd_back_env(env, second_line);
	ft_lstadd_back_env(env, third_line);
}

void	write_env(t_env *env, char **arg)
{
	int		i;

	i = 1;
	while(env)
	{
		if (ft_strchr(env->content, '='))
		{
			ft_putstr_fd(env->content, 1);
			ft_putstr_fd("\n", 1);
		}
		env = env->next;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}