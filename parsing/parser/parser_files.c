/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:36:03 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/24 10:12:01 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int handel_heredoc(char *del)
{
    int fd_in;
    char *line;
    int pid;
    int exit_status;

    fd_in = open("/tmp/test.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
    pid = fork();
    if (pid == -1)
        return (perror("Error forking process"), -1);
    else if (pid == 0)
	{ 
        signal(SIGINT, SIG_DFL);
		rl_catch_signals = 1; 
        while (1)
		{
            line = readline(">");
            if (!line || ft_strcmp(line, del) == 0) {
                free(line);
                break;
            }
            ft_putstr_fd(line, fd_in);
            free(line);
        }
        close(fd_in);
        exit(0); // Child process exits
    } 
	else
	{ 
		wait(&exit_status); 
        if (WIFSIGNALED(exit_status) && WTERMSIG(exit_status) == SIGINT)
			return -2;
    }
    return fd_in;
}


int save_heredoc(t_lexer **lexer)
{
	int len;
	char *del;
	int fd;

	len = 0;
	del = NULL;
	(*lexer) = (*lexer)->next;
	while ((*lexer) && ((*lexer)->token == delimiter ||
						(*lexer)->token == heredoc))
	{
		if ((*lexer)->token == delimiter)
		{
			del = ft_strdup((*lexer)->str);
			fd = handel_heredoc(del);
		}
		(*lexer) = (*lexer)->next;
	}
	return (fd);
}

void show_file_error(int fd, t_token token)
{
	if (fd == -1 && token == redirect_out)
		(error_msg("No such file or directory"));
	else if (fd == -1 && token == redirect_in)
		(error_msg("Error in open file"));
}

int open_files(t_lexer **lexer, t_token token)
{
	int len;
	char *mfile;
	int fd;

	len = 0;
	(*lexer) = (*lexer)->next;
	while ((*lexer) && ((*lexer)->token == file || (*lexer)->token == token))
	{
		if ((*lexer)->token == file && ((*lexer)->next == NULL ||
										(*lexer)->next->token != token))
			mfile = ft_strdup((*lexer)->str);
		(*lexer) = (*lexer)->next;
	}
	if (mfile && !*mfile)
		return (error_msg("ambiguous redirect"), -1);
	if (token == redirect_out)
		fd = open(mfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (token == redirect_in)
		fd = open(mfile, O_RDONLY, 0644);
	else
		fd = open(mfile, O_CREAT | O_RDWR | O_APPEND, 0644);
	show_file_error(fd, token);
	return (fd);
}
