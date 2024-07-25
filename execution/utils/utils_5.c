/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:35:27 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/25 01:34:48 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execut_cmd(t_env **list_env, char **nood, t_simple_cmds *cmds, int len)
{
	char	**env;

	(void) cmds;
	(void) len;
	env = change_list_to_env(*list_env);
	ft_exec (nood, env);
}
