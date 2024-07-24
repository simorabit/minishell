/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:04:10 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/24 01:14:31 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset(t_env **list_env, char *arg)
{
	t_env	*tmp;
	char	*str;

	if (!list_env || !*list_env || !arg)
		return ;
	tmp = *list_env;
	str = get_env_eq(tmp->content);
	if (!ft_strcmp(str, arg))
	{
		*list_env = tmp->next;
		free(tmp);
	}
	else
		unset(&(*list_env)->next, arg);
}
