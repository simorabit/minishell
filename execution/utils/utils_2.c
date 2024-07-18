#include "../../minishell.h"

void	putstr(char *str, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		write (1, &str[j], 1);
		j++;
	}
}

char	*ft_find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp("PATH=", env[i], 5) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
	return (env[i] + 5);
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
		path = ft_split_exe(ft_find_path(env), ':');
		while (path[i])
		{
			if (!ft_strncmp(cmd, path[i], ft_strlen(path[i])))
				j += 1;
			i++;
		}
		i = 0;
		while (i < 39)
		{
			if (!ft_strcmp(get_content_from_eq_to_fin(env[i]), cmd))
				x++;
			i++;
		}
		if (!j && !x)
		{
			print_error(cmd, "no_such_file");
			exit (127);
		}
		if (!j && x)
		{
			print_error(cmd, "is_a_direc");
			exit (126);
		}
	}
}

char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	**all_path;
	char	*one_path;
	char	*cmd_with_path;

	i = 0;
	all_path = ft_split_exe(ft_find_path(env), ':');
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
	//char	**cmmd;

	i = 0;
	if (!ft_strncmp(cmd[0], "\0", 1))
	{
		exit (EXIT_FAILURE);
	}
	//cmmd = ft_split(cmd, ' ');
	//cmd = cmmd[0];
	ft_check(cmd[0], env);
	path = ft_get_path(cmd[0], env);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: ", 2);;
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return ;
	}
	if (execve(path, cmd, env) == -1)
	{
		ft_putstr_fd("minishell: ", 2);;
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free (path);
		free_double_ptr(cmd);
		exit (127);
	}
	free (path);
	free_double_ptr(cmd);
}
