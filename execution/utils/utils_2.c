/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 12:40:14 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/27 04:29:31 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_find_path(char **env, char *var, int j)
{
	int		i;
	int		x;
	char	*ptr;

	ptr = (char *)my_alloc(sizeof(char *) * 1337);
	i = 0;
	x = 0;
	while (env[i] && ft_strncmp(var, env[i], ft_strlen(var)) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	while (env[i][j])
	{
		ptr[x] = env[i][j];
		x++;
		j++;
	}
	ptr[x] = '\0';
	return (ptr);
}

int	check_is_dir(char *cmd)
{
	int			re;
	struct stat	st;

	re = stat(cmd, &st);
	if (!re)
	{
		if (S_ISREG(st.st_mode))
			return (1);
		if (S_ISDIR(st.st_mode))
			return (2);
		return (0);
	}
	return (-1);
}

void	ft_check(char *cmd, char **env)
{
	int		i;
	int		j;
	int		x;
	char	**path;

	i = 0;
	j = 0;
	x = 0;
	if (ft_strchr(cmd, '/'))
	{
		is_error(cmd);
		path = ft_split_exe(ft_find_path(env, "PATH=", 5), ':');
		if (!path)
			return ;
		while (path[i])
		{
			if (!ft_strncmp(cmd, path[i], ft_strlen(path[i]))
				&& ft_strcmp(cmd, path[i]))
				j += 1;
			i++;
		}
		if (j)
			return ;
	}
}

char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	**all_path;
	char	*one_path;
	char	*cmd_with_path;

	i = 0;
	all_path = ft_split_exe(ft_find_path(env, "PATH=", 5), ':');
	if (all_path == NULL)
		return (NULL);
	while (all_path[i])
	{
		one_path = ft_strjoin(all_path[i], "/");
		cmd_with_path = ft_strjoin(one_path, cmd);
		if (access(cmd_with_path, X_OK) == 0)
		{
			free_double_ptr(all_path);
			free(one_path);
			return (cmd_with_path);
		}
		free(cmd_with_path);
		free(one_path);
		i++;
	}
	free_double_ptr(all_path);
	return (ft_strdup(cmd));
}

void	ft_exec(char **cmd, char **env)
{
	int		i;
	char	*path;

	i = 0;
	ft_check(cmd[0], env);
	path = ft_get_path(cmd[0], env);
	if (path == NULL)
	{
		is_error(cmd[0]);
		print_error(cmd[0], "no_such_file");
		exit (127);
	}
	if (execve(path, cmd, env) == -1)
	{
		print_error(cmd[0], "cmd_not_found");
		free_double_ptr(cmd);
		exit (127);
	}
	free (path);
	free_double_ptr(cmd);
}
