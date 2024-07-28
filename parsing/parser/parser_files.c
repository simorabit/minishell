/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:36:03 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/28 15:19:31 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	show_file_error(int fd, int token, char *str, t_simple_cmds **cmds, t_env **env)
{
	if(cmds && *cmds)
	{
		if((*cmds)->in_file == -1 || (*cmds)->aout_file == -1 || (*cmds)->out_file == -1)
			return ;
	}
	if (fd == -1 && token == redirect_out)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Error in open file", 2);
		ft_putstr_fd("\n", 2);
		modify_exit_status(1, env);
	}
	else if (fd == -1 && (token == redirect_in || token == redirect_app))
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": No such file or directory", 2);
		ft_putstr_fd("\n", 2);
		modify_exit_status(1, env);
	}
}

int	open_files(t_lexer **lexer, t_token token, t_simple_cmds **cmds, t_env **env)
{
	int		len;
	char	*mfile;
	int		fd;
	t_lexer *tmp;

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
	if (token == redirect_out)
		fd = open(mfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (token == redirect_in)
		fd = open(mfile, O_RDONLY, 0644);
	if (token == redirect_app)
		fd = open(mfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	show_file_error(fd, token, tmp->str, cmds, env);
	return (fd);
}
