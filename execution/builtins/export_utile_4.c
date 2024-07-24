/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utile_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:40:01 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/24 01:12:10 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*env_dup(t_env *list)
{
	t_env	*nood;
	t_env	*new_list;

	new_list = NULL;
	if (list == NULL)
		return (NULL);
	while (list)
	{
		nood = ft_lstnew_env(list->content);
		ft_lstadd_back_env(&new_list, nood);
		list = list->next;
	}
	return (new_list);
}
