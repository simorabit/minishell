#include "../../minishell.h"

void	child(char *nood, char **env)
{
	char **cmmd;

	cmmd = ft_split_exe(nood, 32);
	// dup2(nood->infile, 0);
	// dup2(nood->outfile, 1);
	// close(nood->infile);
	// close(nood->outfile);
	ft_exec(cmmd, env);
}

void	parent(char *nood, char **env)
{
	(void)env;
	(void)nood;
	wait(NULL);
}
void	initialize_files(t_simple_cmds	*list)
{
	if (list == NULL)
		return ;
	if (list->in_file == -2)
		list->in_file = 0;
	if (list->out_file == -2)
		list->out_file = 1;
}