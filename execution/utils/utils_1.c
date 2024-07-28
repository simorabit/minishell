/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:28:01 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/28 15:20:28 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int check_to_print_exit(int len)
{
	if (len > 1)
		return (1);
	else
		return (0);
}

void initialize_files(t_simple_cmds **list)
{
	t_simple_cmds *tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp == NULL)
			return;
		if (tmp->in_file == -2)
			tmp->in_file = 0;
		if (tmp->out_file == -2 && tmp->aout_file == -2)
			tmp->out_file = 1;
		tmp = tmp->next;
	}
}
