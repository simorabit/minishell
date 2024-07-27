/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_devision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:25:57 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/27 02:38:58 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	multiple_cmd_util_0(t_var **var, t_simple_cmds *list, t_env **env_list, int len)
{
	(*var)->p_in = dup (0);
	(*var)->p_out = dup (1);
	Reducing(list, &(*var)->hold_fd_in);
	(*var)->check = check_is_biltus(list->cmmd[0]);
	if (len > 1 || !(*var)->check)
		(*var)->pid = fork();
	if (len == 1 && (*var)->check)
	{
		(*var)->exit_status = run_built(env_list, list->cmmd, list, len);
		(*var)->i = 1;
	}
}

void	multiple_cmd_util_1(int in_file, int *hold_fd_in)
{
	if (in_file > 0)
	{
		if (*hold_fd_in > 0)
			close (*hold_fd_in);
		dup2(in_file, 0);
		close (in_file);
	}
}

void	multiple_cmd_util_2(int *hold_fd_in)
{
	if (*hold_fd_in > 0)
	{
		dup2(*hold_fd_in, 0);
		close (*hold_fd_in);
	}
}

void	multiple_cmd_util_3(t_simple_cmds *list, int *hold_fd_in)
{
	int	p_fd[2];

	if (list->next)
		{
			if (pipe(p_fd) == -1)
				exit(1);
			dup2(p_fd[1], 1);
			close (p_fd[1]);
			*hold_fd_in = p_fd[0];
		}
}

void	multiple_cmd_util_4(t_simple_cmds *list)
{
	if (list->out_file > 1)
	{
		dup2(list->out_file, 1);
		close (list->out_file);
	}
}

