#include "../../minishell.h"

int	print_error(char *cmd, char *type)
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
	else if (!ft_strcmp(type, "no_such_file"))
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
	ptr = (char *)malloc(sizeof(char) * (len + 1));
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

	if (!cmd)
		return (0);
	if (!ft_strncmp("export", cmd, 6))
		i++;
	else if (!ft_strncmp("echo", cmd, 4))
		i++;
	else if (!ft_strncmp("pwd", cmd, 3))
		i++;
	else if (!ft_strncmp("env", cmd, 3))
		i++;
	else if (!ft_strncmp("cd", cmd, 2))
		i++;
	else if (!ft_strncmp("exit", cmd, 4))
		i++;
	else if (!ft_strncmp("unset", cmd, 5))
		i++;
	return (i);
}

int	run_built(t_env **list_env, char **nood, t_simple_cmds *cmds, int len)
{
	char	*pwd;  
	int		i;

	pwd = NULL;
	i = -1;
	if (nood == NULL)
		return (0);
	if (!ft_strcmp("export", nood[0]))
	{
		export_exe(nood, *list_env);
		return (1);
	}
	else if (!ft_strcmp("echo", nood[0]))
	{
		echo(nood, cmds);
		return (1);
	}
	else if (!ft_strcmp("pwd", nood[0]))
	{
		ft_find_pwd();
		return (1);
	}
	else if (!ft_strcmp("env", nood[0]))
	{
		write_env(*list_env, nood);
		return (1);
	}
	else if (!ft_strcmp("cd", nood[0]))
	{
		cd_exec(cmds, *list_env);
		return (1);
	}
	else if (!ft_strcmp("exit", nood[0]))
	{
		exit_builtins(cmds, nood, len);
		return (1);
	}
	else if (!ft_strcmp("unset", nood[0]))
	{
		while (nood[++i])
			unset(list_env, nood[i]);
		return (1);
	}
	else
		print_error(nood[0], "cmd_not_found");
	return (0);
}

void	multiple_cmd(t_env **env_list, t_simple_cmds *list, int len)
{
	int		p_fd[2];
	int		exit_status;
	int		hold_fd_in;
	int		pid;
	int		p_in ;
	int		p_out;
	int		i;
	t_simple_cmds	*tmp;

	hold_fd_in = 0;
	exit_status = 0;
	tmp = list;
	i = 0;
	//list->in_file = open ("Makefile", O_RDONLY , 0644);
	// while (list)
	// {
	// 	change_list(list);
	// 	// printf ("---> %s\n", list->args[0]);
	// 	printf ("cmd : %s %s | infile : %d | outfile : %d\n", list->cmmd[0], list->cmmd[1], list->in_file, list->out_file);
	// 	list = list->next;
	// }
	// exit(0);
	// if (!list->next && check_is_biltus(list->cmmd[0]))
	// {
	// 	// printf("lllll\n");
	// 	run_built(env_list, list->cmmd, list, len);
	// 	return ;
	// }
	while (list)
	{
		p_in = dup (0);
		p_out = dup (1);
		change_list(list);
		if (list->in_file > 0)
		{
			if (hold_fd_in > 0)
				close (hold_fd_in);
			dup2(list->in_file, 0);
			close (list->in_file);
		}
		else if (hold_fd_in > 0)
		{
			dup2(hold_fd_in, 0);
			close (hold_fd_in);
		}
		if (list->next)
		{
			if (pipe(p_fd) == -1)
				exit(1);
			dup2(p_fd[1], 1);
			close (p_fd[1]);
			hold_fd_in = p_fd[0];
		}
		if (list->out_file > 1)
		{
			dup2(list->out_file, 1);
			close (list->out_file);
		}
		// if (!list->next)
		// run_built(env_list, list->cmmd, list, len);
		int	check = check_is_biltus(list->cmmd[0]);
		if (len > 1 || !check)
		{
			pid = fork();
		}
		// printf("kkkkk\n");
		// if (check_is_biltus(list->cmmd[0]))
		// 	return ;
		// while (1)
		// 	;
		if (len == 1 && check)
		{
			run_built(env_list, list->cmmd, list, len);
			i = 1;
		}
		if (pid == 0)
		{
			if (list->in_file > 0)
				close (p_in);
			if (list->out_file > 1)
				close (p_out);
			//ft_exec(list->cmd_, env);
			//printf ("kkk\n");
			// if (!check_is_biltus(list->cmmd[0]))
			// 	run_built(env_list, list->cmmd, list, len);
			if (list->in_file != -1 && list->out_file != -1 && !i && check)
				run_built(env_list, list->cmmd, list, len);
			if (list->in_file != -1 && list->out_file != -1 && !check)
			{
				if (hold_fd_in > 0)
					close (hold_fd_in);
				classification_cmd(env_list, list->cmmd, list, len);
			}
		}
		if (pid < 0)
		{
			printf ("++++++++++++++++++++++\n");
			print_error(NULL, "fork");
		}
		dup2(p_in, 0);
		close (p_in);
		dup2(p_out, 1);
		close (p_out);
		list = list->next;
		if (pid == 0 && len != 1)
		 	exit(0);
	}
	while (wait(&exit_status) != -1)
		;
	exit_status = WIFEXITED(exit_status);
	char *ex_st = ft_strjoin("?=", ft_itoa(exit_status));
	add_variable(*env_list, ex_st, 1);
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