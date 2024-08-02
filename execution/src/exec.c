/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 01:43:35 by souaouri          #+#    #+#             */
/*   Updated: 2024/08/02 17:23:18 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_len(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i += 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = ft_len(n);
	ptr = (char *)my_alloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	if (n < 0)
	{
		ptr[0] = '-';
		n *= -1;
	}
	ptr[len] = '\0';
	while (n)
	{
		ptr[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (ptr);
}

void	wait_func(int exit_status, t_env **env_list, int i, t_cmds *list)
{
	if (i)
	{
		modify_exit_status(exit_status, env_list);
		return ;
	}
	while (wait(&exit_status) != -1)
		;
	if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGINT)
	{
		printf("\n");
		modify_exit_status(130, env_list);
	}
	else if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGQUIT)
		modify_exit_status(131, env_list);
	if (list && !list->is_error)
	{
		exit_status = WEXITSTATUS(exit_status);
		modify_exit_status(exit_status, env_list);
	}
	else
		modify_exit_status(1, env_list);
}

void	multiple_cmd(t_env **env_list, t_cmds *list, int len)
{
	t_var	*var;
	t_cmds	*cmd;

	var = my_alloc(sizeof(t_var));
	if (!initialize_var(&var, list))
		return ;
	while (list)
	{
		if (list->next == NULL)
			cmd = list;
		if (ambugious(&list) == 1)
			continue ;
		multiple_cmd_util_0(&var, list, env_list, len);
		if (var->pid == 0)
		{
			multiple_cmd_util_5(list, var->p_in, var->p_out);
			if (list->in_file != -1 && list->out_file != -1 && !var->i
				&& var->check)
				var->exit_status = run_bui_p(env_list, list->cmmd, list, len);
			if (list->in_file != -1 && list->out_file != -1 && !var->check)
				execut(var, env_list, list);
		}
		multiple_cmd_util_7(&var, &list, len);
	}
	wait_func(var->exit_status, env_list, var->i, cmd);
}
