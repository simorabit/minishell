#include "../minishell.h"

t_simple_cmds	*ft_lstlast_cmd(t_simple_cmds *cmd)
{
	while (cmd)
	{
		if (!cmd->next)
			return (cmd);
		cmd = cmd->next;
	}
	return (cmd);
}

t_simple_cmds	*ft_lstnew_cmd()
{
	t_simple_cmds	*cmd;

	cmd = (t_simple_cmds *)malloc(sizeof(t_simple_cmds));
	if (!cmd)
		return (NULL);
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

int	ft_lstsize_cmd(t_simple_cmds *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_lstadd_back_cmd(t_simple_cmds **cmd, t_simple_cmds *new)
{
	t_simple_cmds	*last;

	if (!cmd)
		return ;
	if (*cmd)
	{
		last = ft_lstlast_cmd(*cmd);
		last->next = new;
		new->prev = last;
	}
	else
		*cmd = new;
}