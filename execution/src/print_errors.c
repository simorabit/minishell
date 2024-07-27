/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:29:04 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/27 01:42:20 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	print_file_and_directory_errors(char *cmd, char *type)
{
	if (!ft_strcmp(type, "no_such_file"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (!ft_strcmp(type, "is_a_direc"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
	}
	else if (!ft_strcmp(type, "Per_denied"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

int	 print_error(char *cmd, char *type)
{
	if (!ft_strcmp(type, "cmd_not_found"))
	{
		ft_putstr_fd("minishell: ", 2);;
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	else if (!ft_strcmp(type, "pars_export"))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else if (!ft_strcmp(type, "fork"))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("fork: Resource temporarily unavailable\n", 2);
	}
	else
		print_file_and_directory_errors(cmd, type);
	return (0);
}
