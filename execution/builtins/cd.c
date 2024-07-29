/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:49:23 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/29 19:15:23 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_path_ret(char *str, t_env *list_env)
{
	int	i;

	i = 0;
	while (list_env)
	{
		if (!ft_strncmp(list_env->content, str, ft_strlen(str)))
			return (ft_substr(list_env->content, ft_strlen(str),
					ft_strlen(list_env->content) - ft_strlen(str)));
		list_env = list_env->next;
	}
	return (NULL);
}

int	specific_path(t_env *list_env, char *str)
{
	char	*tmp;
	int		ret;

	tmp = find_path_ret(str, list_env);
	ret = chdir(tmp);
	free(tmp);
	if (ret != 0)
	{
		str = ft_substr(str, 0, ft_strlen(str) - 1);
		ft_putstr_fd(str, 2);
		free(str);
		ft_putstr_fd(" not set\n", 2);
	}
	return (ret);
}

void	add_path_to_env(t_tools *tools, t_env *list_env, char **env)
{
	int		i;
	char	*tmp;
	t_env	*temp;

	i = 0;
	temp = list_env;
	tools->pwd = ft_find_path(env, "PWD=", 4);
	while (temp)
	{
		if (!ft_strncmp(temp->content, "PWD=", 4))
		{
			tmp = ft_strjoin("PWD=", tools->pwd);
			free(ft_strdup(temp->content));
			temp->content = tmp;
		}
		else if (!ft_strncmp(temp->content, "OLDPWD=", 7) && tools->old_pwd)
		{
			tmp = ft_strjoin("OLDPWD=", tools->old_pwd);
			free(ft_strdup(temp->content));
			temp->content = tmp;
		}
		temp = temp->next;
	}
}

int	mini_cd(t_tools *tools, t_cmds *s_cmd, t_env *list_env, char **env)
{
	int		ret;
	char	*free_one;

	if (check_for_arg_cd(s_cmd->cmmd[1]))
		ret = specific_path(list_env, "HOME=");
	else if (ft_strcmp(s_cmd->cmmd[1], "-") == 0)
	{
		ret = specific_path(list_env, "OLDPWD=");
		ft_putstr_fd(tools->old_pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ret = chdir(s_cmd->cmmd[1]);
		if (!getcwd(NULL, sizeof(NULL)))
			cd_error();
		if (ret != 0)
			return (builtins_print_error(s_cmd->cmmd[1], "no_such_file"));
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	free_one = change_path_cd(tools);
	free (free_one);
	add_path_to_env(tools, list_env, env);
	return (EXIT_SUCCESS);
}

int	cd_exec(t_cmds *cmds, t_env *list_env)
{
	t_tools	*tools;
	char	**env;
	int		re;

	tools = my_alloc(sizeof(t_tools));
	if (tools == NULL)
		return (0);
	env = change_list_to_env(list_env);
	tools->pwd = ft_find_path(env, "PWD=", 4);
	tools->old_pwd = ft_find_path(env, "OLDPWD=", 7);
	re = mini_cd(tools, cmds, list_env, env);
	free(tools);
	return (re);
}
