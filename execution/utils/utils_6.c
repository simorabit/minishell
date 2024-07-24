/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:24:08 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/24 01:20:03 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**change_list_to_env(t_env *list_env)
{
	char	**env;
	int		i;

	i = 0;
	env = my_alloc(1024);
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
