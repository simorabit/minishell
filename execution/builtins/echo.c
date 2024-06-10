#include "../../minishell.h"


void	echo(char **cmd)
{
	int		i;
	int		v;

	i = 1;
	v = 0;

	if (cmd[i] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	if (!ft_strncmp(cmd[i], "-n", 2))
	{
		i++;
		v++;
	}
	while (cmd[i])   // SEG
	{
		// if (cmd[i][0] == '$')
		// {
		// 	char	*var;
		// 	var = getenv(cmd[i] + 1);
		// 	printf ("====%s\n", cmd[i]);
		// 	if (var)
		// 		ft_putstr_fd(var, 1);
		// }
		
		ft_putstr_fd(cmd[i], 1);
		
			if (cmd[i + 1])
				ft_putstr_fd(" ", 1);
		i++;
	}
	if (!v)
		ft_putstr_fd("\n", 1);
}
