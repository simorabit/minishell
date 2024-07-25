/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:49:23 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/25 02:23:32 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*change_path(t_tools *tools)
{
	char	*tmp;

	tmp = ft_strdup(tools->pwd);
	free(tools->old_pwd);
	tools->old_pwd = tmp;
	free(tools->pwd);
	tools->pwd = getcwd(NULL, sizeof(NULL));
	return (tools->pwd);
}

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

void	add_path_to_env(t_tools *tools, t_env *list_env)
{
	int		i;
	char	*tmp;
	t_env	*temp;

	i = 0;
	temp = list_env;
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

int	builtins_print_error(char *cmd, char *type)
{
	if (!ft_strcmp(type, "pars_export"))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	else if (!ft_strcmp(type, "no_such_file"))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int	mini_cd(t_tools *tools, t_simple_cmds *simple_cmd, t_env *list_env)
{
	int		ret;
	char	*free_one;

	if (!simple_cmd->cmmd[1])
		ret = specific_path(list_env, "HOME=");
	else if (ft_strncmp(simple_cmd->cmmd[1], "-", 1) == 0)
	{
		ret = specific_path(list_env, "OLDPWD=");
		ft_putstr_fd(tools->old_pwd, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		ret = chdir(simple_cmd->cmmd[1]);
		if (ret != 0)
			return (builtins_print_error(simple_cmd->cmmd[1], "no_such_file"));
	}
	if (ret != 0)
		return (EXIT_FAILURE);
	free_one = change_path(tools);
	free (free_one);
	add_path_to_env(tools, list_env);
	return (EXIT_SUCCESS);
}

int	cd_exec(t_simple_cmds *cmds, t_env *list_env)
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
	re = mini_cd(tools, cmds, list_env);
	free(tools);
	return (re);
}
