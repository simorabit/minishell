/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:35:27 by souaouri          #+#    #+#             */
/*   Updated: 2024/06/10 18:07:39 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_fork(char *nood, t_env *list_env) // ???
{
	char	**env;
	int	i;
	int	pid;

	i = 0;
	env = change_list_to_env(list_env);
	pid = fork();
	if (pid == -1)
		perror("error lalala");
	else if (!pid)
		child(nood, env);
	else if (pid)
		parent (nood, env);
}

void	classification_cmd(t_env *list_env, char **nood)
{
	char	*pwd;
	char	**env;

	pwd = NULL;
	

	// (null) kaydkhol lhad if
	if (nood == NULL)
		return ;
	if (!ft_strncmp("export", nood[0], 6))
	{
		export_exe(nood, list_env);
		// export(ft_split("export", ' '), list_env);
		// printf ("\n\n\n");
		// while(list_env)
		// {
		// 	if (ft_strchr(list_env->content, '='))
		// 	{
		// 		ft_putstr_fd(list_env->content, 1);
		// 		ft_putstr_fd("\n", 1);
		// 	}
		// 	list_env = list_env->next;
		// }
	}
	else if (!ft_strncmp("echo", nood[0], 4))
		echo(nood);
	else if (!ft_strncmp("pwd", nood[0], 3))
		ft_find_pwd();
	else if (!ft_strncmp("env", nood[0], 3))
		write_env(list_env);
	else if (!ft_strncmp("cd", nood[0], 2))
		get_cd(*nood);
	else if (!ft_strncmp("export", nood[0], 6))
		export_exe(nood, list_env);
	else
	{
		env = change_list_to_env(list_env);
		ft_exec (nood, env);
	}
	exit(0);   // cmd not found
	//ft_fork(nood, env);
}
