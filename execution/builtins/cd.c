/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 09:49:23 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/15 16:39:41 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_cd(char *cmd)
{
	char	**cmmd;

	cmmd = ft_split_exe(cmd, 32);
	if (chdir(cmmd[1]) != -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(cmmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}
