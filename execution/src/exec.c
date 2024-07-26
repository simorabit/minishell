/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 01:43:35 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/26 09:48:49 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void		print_file_and_directory_errors(char *cmd, char *type)
{
	if (!ft_strcmp(type, "no_such_file"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (!ft_strcmp(type, "is_a_direc"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else if (!ft_strcmp(type, "Per_denied"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

int	 print_error(char *cmd, char *type)
{
	if (!ft_strcmp(type, "cmd_not_found"))
	{
		ft_putstr_fd("minishell: ", 2);;
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	else if (!ft_strcmp(type, "pars_export"))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else if (!ft_strcmp(type, "fork"))
	{
		ft_putstr_fd("minishell:", 2);
		ft_putstr_fd("fork: Resource temporarily unavailable", 2);
	}
	else
		print_file_and_directory_errors(cmd, type);
	return (0);
}

int	ft_len(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i += 1;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = ft_len(n);
	ptr = (char *)my_alloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	if (n < 0)
	{
		ptr[0] = '-';
		n *= -1;
	}
	ptr[len] = '\0';
	while (n)
	{
		ptr[len - 1] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (ptr);
}

int	check_is_biltus(char *cmd)
{
	int	i;

	i = 0;
	if (cmd == NULL || *cmd == '\0')
		return (0);
	if (!ft_strncmp("export", cmd, 6))
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

int	run_built_1(t_env **list_env, char **nood, t_simple_cmds *cmds)
{
	int exit_status;
	
	exit_status = 0;
	if (!ft_strcmp("export", nood[0]))
		exit_status = export_exe(nood, *list_env);
	if (!ft_strcmp("echo", nood[0]))
		echo(nood, cmds);
	if (!ft_strcmp("pwd", nood[0]))
		ft_find_pwd();
	if (!ft_strcmp("env", nood[0]))
		write_env(*list_env, nood);
	return(exit_status);
}

int	run_built_2(t_env **list_env, char **nood, t_simple_cmds *cmds, int len)
{
	int	i;
	int	exit_status;

	i = -1;
	exit_status = 0;
	if (!ft_strcmp("cd", nood[0]))
		exit_status = cd_exec(cmds, *list_env);
	if (!ft_strcmp("exit", nood[0]))
		exit_builtins(cmds, nood, len);
	if (!ft_strcmp("unset", nood[0]))
	{
		while (nood[++i])
			unset(list_env, nood[i]);
		return (1);
	}
	return(exit_status);
}

int	run_built(t_env **list_env, char **nood, t_simple_cmds *cmds, int len)
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
	exit_status = run_built_2(list_env, nood, cmds, len);
	return (exit_status);
}

void	multiple_cmd_util_1(int in_file, int *hold_fd_in)
{
	if (in_file > 0)
	{
		if (*hold_fd_in > 0)
			close (*hold_fd_in);
		dup2(in_file, 0);
		close (in_file);
	}
}

void	multiple_cmd_util_2(int *hold_fd_in)
{
	if (*hold_fd_in > 0)
	{
		dup2(*hold_fd_in, 0);
		close (*hold_fd_in);
	}
}

void	multiple_cmd_util_3(t_simple_cmds *list, int *hold_fd_in)
{
	int	p_fd[2];

	if (list->next)
		{
			if (pipe(p_fd) == -1)
				exit(1);
			dup2(p_fd[1], 1);
			close (p_fd[1]);
			*hold_fd_in = p_fd[0];
		}
}

void	multiple_cmd_util_4(t_simple_cmds *list)
{
	if (list->out_file > 1)
	{
		dup2(list->out_file, 1);
		close (list->out_file);
	}
}

void	multiple_cmd_util_5(t_simple_cmds *list, int p_in, int p_out)
{
	if (list->in_file == 0)
		close (p_in);
	if (list->out_file == 1)
		close (p_out);
}

void	multiple_cmd_util_6(int p_in, int p_out)
{
	dup2(p_in, 0);
	close (p_in);
	dup2(p_out, 1);
	close (p_out);
}

void	Reducing(t_simple_cmds *list, int *hold_fd_in)
{
	change_list(list);
	multiple_cmd_util_1(list->in_file, hold_fd_in);
	multiple_cmd_util_2(hold_fd_in);
	multiple_cmd_util_3(list, hold_fd_in);
	multiple_cmd_util_4(list);
}

void	initialize_util(t_util *util, int i, int len, int check, int h)
{
	util->i = i;
	util->len = len;
	util->check = check;
	util->hold = h; 
}

void	run_cmd(t_env **env_list, t_simple_cmds *list, t_util *util)
{
	if (list->in_file != -1 && list->out_file != -1 && !util->i && util->check)
		run_built(env_list, list->cmmd, list, util->len);
	if (list->in_file != -1 && list->out_file != -1 && !util->check)
	{
		if (util->hold > 0)
			close (util->hold);
		execut_cmd(env_list, list->cmmd, list, util->len);
	}
}

void	wait_func(int exit_status, t_env **env_list, int i)
{
	if (i)
	{
		char *ex_st = ft_strjoin("?=", ft_itoa(exit_status));
		add_variable(*env_list, ex_st, 1);
		return ;
	}
	while (wait(&exit_status) != -1)
		;
	exit_status = WEXITSTATUS(exit_status);
	char *ex_st = ft_strjoin("?=", ft_itoa(exit_status));
	add_variable(*env_list, ex_st, 1);
}

void	multiple_cmd(t_env **env_list, t_simple_cmds *list, int len)
{
	int		exit_status;
	int		hold_fd_in;
	int		pid;
	int		p_in ;
	int		p_out;
	int		i;
	t_util	*util;

	if (!list || !list->cmd)
		return ;
	hold_fd_in = 0;
	exit_status = 0;
	i = 0;
	util = NULL;
	while (list)
	{
		p_in = dup (0);
		p_out = dup (1);
		// while (list)
		// {
		// 	change_list(list);
		// 	// printf ("---> %s\n", list->args[0]);
		// 	printf ("cmd : %s | {{{%s}}} | infile : %d | outfile : %d\n", list->cmd, list->args[0], list->in_file, list->out_file);
		// 	list = list->next;
		// }
		Reducing(list, &hold_fd_in);
		int	check = check_is_biltus(list->cmmd[0]);
		if (len > 1 || !check)
			pid = fork();
		if (len == 1 && check)
		{
			exit_status = run_built(env_list, list->cmmd, list, len);
			i = 1;
		}
		if (pid == 0)
		{
			multiple_cmd_util_5(list, p_in, p_out);
			//initialize_util(util, i, len, check, hold_fd_in);
			if (list->in_file != -1 && list->out_file != -1 && !i && check)
				run_built(env_list, list->cmmd, list, len);
			if (list->in_file != -1 && list->out_file != -1 && !check)
			{
				if (hold_fd_in > 0)
					close (hold_fd_in);
				execut_cmd(env_list, list->cmmd, list, len);
			}
		}
		if (pid < 0)
			print_error(NULL, "fork");
		multiple_cmd_util_6(p_in, p_out);
		list = list->next;
		if (pid == 0 && len != 1)
		 	exit(0);
	}
	wait_func(exit_status, env_list, i);
}
	/*
	while (head)
	{
		int fd_inparent= dup(0);
		int fd_outparent= dup(1);
		if(data->next)
		{
			int *ptr = creatpipe();
			dup2(ptr[1], 1);
			int hold_fdin = ptr[0];
		}
		if(data->fdin >  1)
		{
			close(hold_fdin);
			daup2(fdin, 0);
			close(fdin);
		}
		else if (hold_fdin > 0)
		{
			daup2(hold_fdin, 0);
			close(hold_fdin);
		}
		pid = fork();
		if (pid == 0)
		{
			
			run_cammand(**env, **cmd);
		}
		else if (pid < 0)
		{
			message : wahh wahh alyamm !
		}

		head = head->next;

	}
	
	
	
	
	*/