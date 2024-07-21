/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utile_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:39:57 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/21 18:41:03 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_for_plus_and_eq(char *arg, int w)
{
	int	i;
	char	*first_part;

	i = 0;
	first_part = get_var_from_beg_to_eq(arg);
	while (arg[i + 1])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
		{
			i = -1;
			break ;
		}
		i++;
	}
	if ((check_arg_is_valide(first_part) || check_for_first_char(first_part)) && i == -1)
	{
		if (w == 1)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (-1);
		}
	}
	i = 0;
	while (arg[i + 1])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}


char	*remove_plus(char *new)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = my_alloc(ft_strlen(new) + 1, 'a');
	
	while (new[i])
	{
		if (new[i] != '+')
		{
			ptr[j] = new[i];
			j++;
		}
		i++;
	}
	ptr[j] = '\0';
	return (ptr);
}

// void	remove_var(t_env *list_env, char *var)
// {
// 	while (list_env)
// 	{
// 		if (ft_strncmp(list_env->content, var, ft_strlen(var)) == 0)
// 		{
// 			list_env = list_env->next;
// 		}
// 		list_env = list_env->next;
// 	}
// }


char	*find_var(t_env *list_env, char	*var)
{
	while (list_env)
	{
		if (ft_strncmp(list_env->content, var, ft_strlen(var)) == 0)
		{
			// printf ("--->list : %s    ---->new var : %s\n", list_env->content, var);
			return (list_env->content);
		}
		list_env = list_env->next;
	}
	return (NULL);
}

