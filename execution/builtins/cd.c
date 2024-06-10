#include "../../minishell.h"

void	get_cd(char *cmd)
{
	char	**cmmd;

	cmmd = ft_split_exe(cmd, 32);
	if (chdir(cmmd[1]) != 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}
