#include "../../minishell.h"

void	multiple_cmd(t_env *env_list, t_simple_cmds *list)
{
	int		p_fd[2];
	int		hold_fd_in;
	int		pid;
	int		p_in ;
	int		p_out;
	t_simple_cmds	*tmp;

	hold_fd_in = 0;
	tmp = list;
	// while (list)
	// {
	// 	change_list(list);
	// 	printf ("cmd : %s %s | infile : %d | outfile : %d\n", list->content.cmmd[0], list->content.cmmd[1], list->content.infile, list->content.outfile);
	// 	list = list->next;
	// }
	// exit (0);
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
			classification_cmd(env_list, list->cmmd);
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