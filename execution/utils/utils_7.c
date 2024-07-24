/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:00:13 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/24 01:20:37 by souaouri         ###   ########.fr       */
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
		return (ft_split_exe(cmd, ' '));
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
