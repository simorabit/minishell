#include "../../minishell.h"
int handel_heredoc(char *del)
{
    int fd_in;
    char *line;
    char *limiter;
    
    fd_in = open("/tmp/test.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
    if (fd_in == -1)
        (perror("Error in open file"));
    else
    {
        line = get_next_line(0);
        limiter = ft_strjoin(del, "\n");
        if(!limiter)
            return -2;
        while (ft_strncmp(line, limiter, ft_strlen(limiter)))
        {
            ft_putstr_fd(line, fd_in);
            free(line);
            line = get_next_line(0);
            if (!line)
                break;
        }
    }
    return fd_in;
}
int save_heredoc(t_lexer **lexer)
{
    int len;
    char *del;
    int fd;

    len = 0;
    (*lexer) = (*lexer)->next;
    while ((*lexer) && ((*lexer)->token == delimiter || (*lexer)->token == heredoc))
    {
        if ((*lexer)->token == delimiter && ((*lexer)->next == NULL ||
                    (*lexer)->next->token == mpipe))
            del = ft_strdup((*lexer)->str);
        (*lexer) = (*lexer)->next;
    }
    fd = handel_heredoc(del);
    return (fd);
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
    if(mfile && !*mfile)
        return (error_msg("ambiguous redirect"), -1);
    if (token == redirect_out)
        fd = open(mfile, O_RDONLY , 0644);
    else if (token == redirect_in)
        fd = open(mfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    else 
        fd = open(mfile, O_CREAT | O_RDWR | O_APPEND, 0644);
    if (fd == -1 && token == redirect_out)
        (error_msg("No such file or directory"));
    else
        (error_msg("Error in open file"));
    return fd;
}
