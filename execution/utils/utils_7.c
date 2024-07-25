/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:00:13 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/25 00:50:28 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	len_of_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i + 1);
}

char	**creat_a_cmd(char *cmd)
{
	char	**cmmd;
	char	**cmmd_1;
	char	*join;
	int		i;

	i = 0;
	cmmd_1 = ft_split_exe(cmd, ' ');
	cmmd = my_alloc(sizeof(char *) * (len_of_arg(cmmd_1) + 1));
	join = NULL;
	while (cmmd_1[i] != NULL)
	{
		if (len_of_arg(cmmd_1) == 2)
		{
			cmmd[0] = ft_strjoin(cmmd_1[0], cmmd_1[1]);
			break ;
		}
		if (cmmd[0])
			join = ft_strjoin(cmmd[0], " ");
		cmmd[0] = ft_strjoin(join, cmmd_1[i]);
		i++;
	}
	return (cmmd);
}

char	**join_cmd_arg(char *cmd, char **arg)
{
	int		i;
	int		j;
	char	**ptr;
	ptr = NULL;
	i = 0;
	j = 0;
	if (cmd == NULL && arg == NULL)
		return (NULL);
	else if (cmd == NULL)
		return (arg);
	else if (arg == NULL)
		return (creat_a_cmd(cmd));
	ptr = my_alloc(sizeof(char *) * (len_of_arg(arg) + 1));
	ptr[0] = cmd;
	i++;
	while (arg[j])
	{
		ptr[i] = arg[j];
		i++;
		j++;
	}
	ptr[i] = NULL;
	return (ptr);
}
