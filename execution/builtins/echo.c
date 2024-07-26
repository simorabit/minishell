/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:49:32 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/04 09:49:32 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	int	check_arg_is_null(char *cmd)
{
	if (cmd == NULL)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	return (1);
}

void	echo(char **cmd, t_simple_cmds *cmds)
{
	int	i;
	int	v;

	i = 1;
	v = 0;
	if (!check_arg_is_null(cmd[i]))
		return ;
	if (!ft_strncmp(cmd[i], "-n", 2) && ft_strlen_1(cmds->args) > 1)
	{
		i++;
		v++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!v)
		ft_putstr_fd("\n", 1);
}
