/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:31:39 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/31 21:08:53 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_is_biltus(char *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL || *cmd == '\0')
		return (0);
	if (!ft_strcmp("export", cmd))
		i++;
	else if (!ft_strcmp("echo", cmd))
		i++;
	else if (!ft_strcmp("pwd", cmd))
		i++;
	else if (!ft_strcmp("env", cmd))
		i++;
	else if (!ft_strcmp("cd", cmd))
		i++;
	else if (!ft_strcmp("exit", cmd))
		i++;
	else if (!ft_strcmp("unset", cmd))
		i++;
	return (i);
}

int	run_built_1(t_env **list_env, char **nood, t_cmds *cmds)
{
	int	exit_status;

	exit_status = 0;
	if (!ft_strcmp("export", nood[0]))
		exit_status = export_exe(nood, *list_env);
	else if (!ft_strcmp("echo", nood[0]))
		echo(nood, cmds);
	else if (!ft_strcmp("pwd", nood[0]))
		ft_find_pwd(*list_env);
	else if (!ft_strcmp("env", nood[0]))
		write_env(*list_env, nood);
	else
		return (-1);
	return (exit_status);
}

int	run_built_2(t_env **list_env, char **nood, t_cmds *cmds, int len)
{
	int	i;
	int	exit_status;

	i = -1;
	exit_status = 0;
	if (!ft_strcmp("cd", nood[0]))
		exit_status = cd_exec(cmds, *list_env);
	else if (!ft_strcmp("exit", nood[0]))
		exit_builtins(cmds, nood, len);
	else if (!ft_strcmp("unset", nood[0]))
	{
		while (nood[++i])
			exit_status = unset(list_env, nood[i]);
	}
	else
		return (-1);
	return (exit_status);
}

int	run_built(t_env **list_env, char **nood, t_cmds *cmds, int len)
{
	char	*pwd;
	char	**env;
	int		exit_status;

	pwd = NULL;
	env = change_list_to_env(*list_env);
	if (nood == NULL)
		return (0);
	if (!ft_find_path(env, "PATH=", 5))
	{
		print_error(nood[0], "no_such_file");
		return (127);
	}
	exit_status = run_built_1(list_env, nood, cmds);
	if (exit_status == -1)
		exit_status = run_built_2(list_env, nood, cmds, len);
	if (exit_status == -1)
		printf ("rah makaynch \n");
	return (exit_status);
}
