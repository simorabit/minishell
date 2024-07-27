/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:28:01 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/27 23:58:26 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_to_print_exit(int len)
{
	if (len > 1)
		return (1);
	else
		return (0);
}

void	initialize_files(t_simple_cmds	*list)
{
	if (list == NULL)
		return ;
	if (list->in_file == -2)
		list->in_file = 0;
	if (list->aout_file > list->out_file)
		list->out_file = list->aout_file;
	if (list->out_file == -2 && list->aout_file == -2)
		list->out_file = 1;
}
