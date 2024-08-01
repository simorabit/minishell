/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:36:03 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/01 17:04:03 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	show_file_error(int fd, int to, char *s, t_env **env)
{
	if (fd == -1 && to == redirect_out)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": Error in open file", 2);
		ft_putstr_fd("\n", 2);
		modify_exit_status(1, env);
	}
	else if (fd == -1 && (to == redirect_in || to == redirect_app))
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": No such file or directory", 2);
		ft_putstr_fd("\n", 2);
		modify_exit_status(1, env);
	}
}

int	check_files_error(t_cmds **cm)
{
	if (cm && *cm)
	{
		if ((*cm)->in_file == -1 || (*cm)->aout_file == -1 || \
			(*cm)->out_file == -1)
			return (1);
	}
	return (0);
}

int	open_files_after_check(int token, char *mfile)
{
	int	fd;

	if (token == redirect_out)
		fd = open(mfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (token == redirect_in)
		fd = open(mfile, O_RDONLY, 0644);
	if (token == redirect_app)
		fd = open(mfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	return (fd);
}

int	open_files(t_lexer **lexer, t_token token, t_cmds **cmds, t_env **env)
{
	int		len;
	char	*mfile;
	int		fd;
	t_lexer	*tmp;

	len = 0;
	(*lexer) = (*lexer)->next;
	tmp = *lexer;
	while ((*lexer) && ((*lexer)->token == file || (*lexer)->token == token))
	{
		if ((*lexer)->token == file && ((*lexer)->next == NULL || \
				(*lexer)->next->token != token))
			mfile = ft_strdup((*lexer)->str);
		(*lexer) = (*lexer)->next;
	}
	if (mfile && !*mfile)
	{
		(*cmds)->is_ambugious = 1;
		return (error_msg(AMBIGUOUS_REDIRECT, env), -1);
	}
	fd = open_files_after_check(token, mfile);
	if (!check_files_error(cmds))
		show_file_error(fd, token, tmp->str, env);
	return (fd);
}
