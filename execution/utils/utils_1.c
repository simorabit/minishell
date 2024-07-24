/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:28:01 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/24 01:15:27 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	initialize_files(t_simple_cmds	*list)
{
	if (list == NULL)
		return ;
	if (list->in_file == -2)
		list->in_file = 0;
	if (list->out_file == -2)
		list->out_file = 1;
}
