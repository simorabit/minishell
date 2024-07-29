/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:49:51 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/29 16:46:43 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	read_herdoc(char *del, char *line, int fd_in)
{
	while (1)
	{
		line = readline(">");
		if (!line || ft_strcmp(line, del) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd_in);
		ft_putstr_fd("\n", fd_in);
		free(line);
	}
}

static void	handel_heredoc_in_child(char *del, char *line, int fd_in)
{
	signal(SIGINT, SIG_DFL);
	rl_catch_signals = 1;
	read_herdoc(del, line, fd_in);
	(close(fd_in), exit(0));
}

int	handel_heredoc(char *del, t_cmds **cmds)
{
	int		fd_in;
	char	*line;
	int		pid;
	int		exit_status;

	line = NULL;
	fd_in = open("/tmp/test.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	pid = fork();
	if (pid == -1)
		return (perror("Error forking process"), -1);
	else if (pid == 0)
		handel_heredoc_in_child(del, line, fd_in);
	else
	{
		wait(&exit_status);
		if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGINT)
		{
			close(fd_in);
			if (cmds && *cmds)
				(*cmds)->stop_ex = 0;
			return (-2);
		}
	}
	fd_in = open("/tmp/test.txt", O_RDONLY, 0644);
	return (fd_in);
}

int	save_heredoc(t_lexer **lexer, t_cmds **cmds)
{
	int		len;
	char	*del;
	int		fd;

	len = 0;
	del = NULL;
	(*lexer) = (*lexer)->next;
	while ((*lexer) && ((*lexer)->token == delimiter || \
		(*lexer)->token == heredoc))
	{
		if ((*lexer)->token == delimiter)
		{
			del = ft_strdup((*lexer)->str);
			fd = handel_heredoc(del, cmds);
			if ((*cmds)->stop_ex == 0)
				break ;
		}
		(*lexer) = (*lexer)->next;
	}
	return (fd);
}
