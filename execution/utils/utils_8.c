/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_8.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 00:51:39 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/29 19:13:39 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	change_list(t_cmds *list)
{
	list->cmmd = join_cmd_arg(list->cmd, list->args);
}

void	execut(t_var *var, t_env **env_list, t_cmds *list)
{
	if (var->hold_fd_in > 0)
		close (var->hold_fd_in);
	execut_cmd(env_list, list->cmmd, list);
}
