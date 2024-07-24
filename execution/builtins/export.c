/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:43:37 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/24 08:04:23 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	_remove_var(t_env *temp, char *new)
{
	char	*ptr;

	while (temp)
	{
		ptr = ft_strjoin(get_env_eq(new), "=");
		if (!ft_strncmp(temp->content, ptr, ft_strlen(ptr))
			|| !ft_strcmp(temp->content, get_env_eq(new)))
		{
			// free(temp->content);
			temp->content = ft_strdup(new);
			free(ptr);
			return (1);
		}
		free(ptr);
		temp = temp->next;
	}
	return (0);
}

int	preparing_var(t_env *list_env, char *new)
{
	char	*join;
	char	*join_1;
	char	*ptr;

	while (list_env)
	{
		ptr = get_var_from_beg_to_eq(new);
		if (!ft_strncmp(list_env->content, ptr, ft_strlen(ptr)))
		{
			if (!ft_strchr(list_env->content, '='))
			{
				join = ft_strjoin(list_env->content, "=");
				list_env->content = ft_strjoin(join, get_eq_to_fin(new));
			}
			else
			{
				join_1 = get_eq_to_fin(new);
				list_env->content = ft_strjoin(list_env->content, join_1);
			}
			return (1);
		}
		list_env = list_env->next;
	}
	return (0);
}

void	add_variable(t_env *list_env, char *new, int error)
{
	t_env	*var;
	t_env	*temp;

	temp = list_env;
	if (check_for_plus_and_eq(new, 0))
		if (preparing_var(list_env, new))
			return ;
	if (_remove_var(temp, new))
		return ;
	if (error != -1)
	{
		var = ft_lstnew_env(new);
		ft_lstadd_back_env(&list_env, var);
	}
}

void	print_export(t_env *list_env)
{
	t_env	*head;
	t_env	*copy_env;

	copy_env = env_dup(list_env);
	ft_sort_env(copy_env);
	head = copy_env;
	while (head)
	{
		// if (!ft_strchr(get_env_eq(head->content), '?'))
		// {
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(add_double_quotes(head->content), 1);
		ft_putstr_fd("\n", 1);
		// }
		head = head->next;
	}
}

void	add_var_exist(char *cmd, t_env *list_env, int error)
{
	char	*var;

	var = ft_strjoin(get_var_from_beg_to_eq(cmd), "=");
	if (!find_var(list_env, var))
	{
		cmd = remove_plus(cmd);
		add_variable(list_env, cmd, error);
	}
	else
		add_variable(list_env, cmd, error);
}

int	if_var_exist_return(char *cmd, t_env *list_env)
{
	char	*var;

	var = ft_strjoin(get_var_from_beg_to_eq(cmd), "=");
	if (find_var(list_env, var))
		return (1);
	return (0);
}

void	export_exe(char **cmd, t_env *list_env)
{
	int		i;
	int		x;
	int		error;

	i = 1;
	x = ft_lstsize_env(list_env);
	if (cmd [0] == NULL || cmd == NULL)
		return ;
	while (cmd[i])
	{
		if (!ft_strchr(cmd[i], '='))
			if (if_var_exist_return(cmd[i], list_env))
				return ;
		error = check_for_plus_and_eq(cmd[i], 1);
		if (error && error != -1 && !check_for_first_char(get_env_eq(cmd[i])))
			add_var_exist(cmd[i], list_env, error);
		else if (!check_arg_is_valide(get_env_eq(cmd[i]))
			&& !check_for_first_char(get_env_eq(cmd[i])))
			add_variable(list_env, cmd[i], error);
		else if (error != -1)
			builtins_print_error(cmd[i], "pars_export");
		i++;
	}
	if (!ft_strcmp(cmd[0], "export") && !cmd[1])
		print_export(list_env);
}
