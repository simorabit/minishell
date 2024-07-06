/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:43:37 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/06 13:00:45 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// int	one_plus(char *str)
// {
// 	int	i;
// 	int	x;

// 	i = 0;
// 	x = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '+')
// 			x++;
// 		i++;
// 	}
// 	if (x == 1)
// 		return (1);
// 	return (0);
// }


void	add_variable(t_env *list_env, char *new, int error)
{
	t_env	*var;
	t_env	*temp;
	int		new_var;
	char	*first_part;
	char	*sec_part;
	char	*ptr;
	
	temp = list_env;
	first_part = NULL;
	sec_part = NULL;
	new_var = 0;
	if (check_for_plus_and_eq(new, 0))
	{
		//exit (0);
		//printf ("gjbfgjbg\n");
		new_var = check_var_does_it_exist(new, list_env);
		if (new_var)
		{
			//remove_var(list_env, get_var_from_beg_to_eq(new));
			first_part = ft_strjoin(get_var_from_beg_to_eq(new), "=");
			ptr = find_var(list_env, first_part);
			sec_part = ft_strjoin(get_content_from_eq_to_fin(ptr), get_content_from_eq_to_fin(new));
			//new = ft_strjoin(first_part, sec_part);
		}
		//printf ("\n\n\n%s\n\n\n", get_var_from_beg_to_eq(new));
		while (list_env)
		{
			char *pptr = get_var_from_beg_to_eq(new);
			if (!ft_strncmp(list_env->content, pptr, ft_strlen(pptr)))
			{
				// printf ("KKKK\n");
				list_env->content = ft_strjoin(list_env->content, get_content_from_eq_to_fin(new));
				return ;
			}
			list_env = list_env->next;
		}
		//new = remove_plus(new);
	}
	// check if the var is in the env
	// is not existed add like this: var = ft_lstnew_env(new);
	// is existed 
	/*
		free(`string`); // var->content
		var->content = ft_strdup(`new_string`);
	*/
	while (temp)
	{
		char *pptr = get_env_eq(new);
		if (!ft_strncmp(temp->content, pptr, ft_strlen(pptr)))
		{
			// printf ("KKKK\n");
			free(temp->content);
			temp->content = ft_strdup(new);
			free(pptr);
			return ;
		}
		free(pptr);
		temp = temp->next;
	}
	// if (one_plus(get_env_eq(new)) && check_for_plus_and_eq(new, 0))
	// {
	//printf ("====> : %d\n" , check_for_plus_and_eq(new, 0));
	if (error != -1)
	{
		var = ft_lstnew_env(new);
		ft_lstadd_back_env(&list_env, var);
	}
	// }
}

void	export_exe(char **cmd, t_env *list_env)
{
	// char	**export;
	t_env	*head;
	t_env	*copy_env;
	int		i;
	int		x;
	char	*var;
	int		error;

	i = 1;
	x = ft_lstsize_env(list_env);
	if (cmd [0] == NULL || cmd == NULL)
		return ;
	while (cmd[i])
	{
		error = check_for_plus_and_eq(cmd[i], 1);
		if (error && !check_for_first_char(get_env_eq(cmd[i])))
		{
			var = get_var_from_beg_to_eq(cmd[i]);
			if (!find_var(list_env, var))
			{
				cmd[i] = remove_plus(cmd[i]);
				add_variable(list_env, cmd[i], error);
			}
			else
			{
				add_variable(list_env, cmd[i], error);
			}
		}
		else if (!check_arg_is_valide(get_env_eq(cmd[i])) && !check_for_first_char(get_env_eq(cmd[i])))
			add_variable(list_env, cmd[i], error);
		else if (error != -1)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
	if (!ft_strncmp(cmd[0], "export", 6) && !cmd[1])
	{
		copy_env = env_dup(list_env);
		ft_sort_env(copy_env);
		head = copy_env;
		while (head)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(add_double_quotes(head->content), 1);
			ft_putstr_fd("\n", 1);
			head = head->next;
		}
	}
}
