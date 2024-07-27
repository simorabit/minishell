/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 01:43:35 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/27 02:52:56 by souaouri         ###   ########.fr       */
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

void	wait_func(int exit_status, t_env **env_list, int i)
{
	if (i)
	{
		char *ex_st = ft_strjoin("?=", ft_itoa(exit_status));
		add_variable(*env_list, ex_st, 1);
		return ;
	}
	while (wait(&exit_status) != -1)
		;
	exit_status = WEXITSTATUS(exit_status);
	char *ex_st = ft_strjoin("?=", ft_itoa(exit_status));
	add_variable(*env_list, ex_st, 1);
}

void	multiple_cmd(t_env **env_list, t_simple_cmds *list, int len)
{
	t_var *var = malloc(sizeof(t_var));

	if (!list || !list->cmd)
		return ;
	// printf ("%s\n", get_var_from_beg_to_eq("salm+=vbbb"));
	// exit (0);
	initialize_var(&var);
	while (list)
	{
		multiple_cmd_util_0(&var, list, env_list, len);
		if (var->pid == 0)
		{
			multiple_cmd_util_5(list, var->p_in, var->p_out);
			if (list->in_file != -1 && list->out_file != -1 && !var->i && var->check)
				var->exit_status = run_built(env_list, list->cmmd, list, len);
			if (list->in_file != -1 && list->out_file != -1 && !var->check)
			{
				if (var->hold_fd_in > 0)
					close (var->hold_fd_in);
				execut_cmd(env_list, list->cmmd, list, len);
			}
		}//
		multiple_cmd_util_7(&var, &list, len);
	}
	wait_func(var->exit_status, env_list, var->i);
}
