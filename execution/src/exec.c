#include "../../minishell.h"

int	check_is_biltus(char **nood)
{
	int	i;

	i = 0;
	if (nood == NULL)
		return (0);
	if (!ft_strncmp("export", nood[0], 6))
		i++;
	else if (!ft_strncmp("echo", nood[0], 4))
		i++;
	else if (!ft_strncmp("pwd", nood[0], 3))
		i++;
	else if (!ft_strncmp("env", nood[0], 3))
		i++;
	else if (!ft_strncmp("cd", nood[0], 2))
		i++;
	else if (!ft_strncmp("exit", nood[0], 4))
		i++;
	else if (!ft_strncmp("unset", nood[0], 5))
		i++;
	return (i);
}

void	run_built(t_env **list_env, char **nood, t_simple_cmds *cmds, int len)
{
	char	*pwd;  
	int		i;

	pwd = NULL;
	i = -1;
	if (nood == NULL)
		return ;
	if (!ft_strncmp("export", nood[0], 6))
		export_exe(nood, *list_env);
	else if (!ft_strncmp("echo", nood[0], 4))
		echo(nood, cmds);
	else if (!ft_strncmp("pwd", nood[0], 3))
		ft_find_pwd();
	else if (!ft_strncmp("env", nood[0], 3))
		write_env(*list_env, nood);
	else if (!ft_strncmp("cd", nood[0], 2))
		get_cd(*nood);
	else if (!ft_strncmp("exit", nood[0], 4))
		exit_builtins(cmds, nood, len);
	else if (!ft_strncmp("unset", nood[0], 5))
		while (nood[++i])
			unset(list_env, nood[i]);
}

void	multiple_cmd(t_env **env_list, t_simple_cmds *list, int len)
{
	int		p_fd[2];
	int		hold_fd_in;
	int		pid;
	int		p_in ;
	int		p_out;
	int		check;
	t_simple_cmds	*tmp;

	hold_fd_in = 0;
	tmp = list;
	//list->in_file = open ("Makefile", O_RDONLY , 0644);
	while (list)
	{
		change_list(list);
		printf ("---> %s\n", list->args[0]);
		// printf ("cmd : %s %s | infile : %d | outfile : %d\n", list->cmmd[0], list->cmmd[1], list->in_file, list->out_file);
		list = list->next;
	}
	exit (0);
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
		pid = fork();
		if (!list->next)
			run_built(env_list, list->cmmd, list, len);
		if (pid == 0)
		{
			close (p_in);
			close (p_out);
			if (hold_fd_in > 0)
				close (hold_fd_in);
			//ft_exec(list->cmd_, env);
			//printf ("kkk\n");
			// while (1)
			// 	;
			check = check_is_biltus(list->cmmd);
			if (list->in_file != -1 && list->out_file != -1 && !check)
				classification_cmd(env_list, list->cmmd, list, len);
		}
		if (pid < 0)
		{
			ft_putstr_fd("minishell:", 2);
			ft_putstr_fd("fork: Resource temporarily unavailable", 2);
		}
		dup2(p_in, 0);
		close (p_in);
		dup2(p_out, 1);
		close (p_out);
		list = list->next;
	}
	while (wait(NULL) != -1)
		;
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