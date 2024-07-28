/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:28:01 by souaouri          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/28 14:10:20 by mal-mora         ###   ########.fr       */
=======
/*   Updated: 2024/07/28 02:18:03 by souaouri         ###   ########.fr       */
>>>>>>> origin/master
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
<<<<<<< HEAD
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
=======
	if (list == NULL)
		return ;
	if (list->heredoc > 2)
		list->in_file = list->heredoc;
	if (list->in_file == -2)
		list->in_file = 0;
	if (list->aout_file > list->out_file)
		list->out_file = list->aout_file;
	if (list->out_file == -2 && list->aout_file == -2)
		list->out_file = 1;
>>>>>>> origin/master
}
