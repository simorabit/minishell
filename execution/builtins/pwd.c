/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:49:51 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/29 16:39:40 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*change_path_cd(t_tools *tools)
{
	char	*tmp;

	if (!tools->pwd || !tools->old_pwd)
		return (NULL);
	tmp = ft_strdup(tools->pwd);
	free(tools->old_pwd);
	tools->old_pwd = tmp;
	free(tools->pwd);
	tools->pwd = getcwd(NULL, sizeof(NULL));
	return (tools->pwd);
}

void	ft_find_pwd(t_env *list_env)
{
	char	*pwd;
	char	**env;

	env = change_list_to_env(list_env);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd("OLDPWD not set", 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ft_putstr_fd(pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	free (pwd);
}
