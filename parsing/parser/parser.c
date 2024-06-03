#include "../minishell.h"
void *save_app_files(t_lexer **lexer, t_simple_cmds *cmds)
{
    t_lexer *tmp;
    int len;
    int i;

    i = 0;
    len = 0;

    tmp = (*lexer)->next;
    while (tmp && tmp->token == word)
    {
        len++;
        tmp = tmp->next;
    }
    cmds->aout_file = malloc((len + 1) * sizeof(char *));
    if (!cmds->aout_file)
        return NULL;
    (*lexer) = (*lexer)->next;
    while (i < len)
    {
        cmds->aout_file[i] = ft_strdup((*lexer)->str);
        i++;
        (*lexer) = (*lexer)->next;
    }
    cmds->aout_file[i] = NULL;
    return NULL;
}
void *save_heredoc(t_lexer **lexer, t_simple_cmds *cmds)
{
    t_lexer *tmp;
    int len;
    int i;

    i = 0;
    len = 0;

    tmp = (*lexer)->next;
    while (tmp && tmp->token == word)
    {
        len++;
        tmp = tmp->next;
    }
    cmds->heredoc = malloc((len + 1) * sizeof(char *));
    if (!cmds->heredoc)
        return NULL;
    (*lexer) = (*lexer)->next;
    while (i < len)
    {
        cmds->heredoc[i] = ft_strdup((*lexer)->str);
        i++;
        (*lexer) = (*lexer)->next;
    }
    cmds->heredoc[i] = NULL;
    return NULL;
}
void *save_out_files(t_lexer **lexer, t_simple_cmds *cmds)
{
    t_lexer *tmp;
    int len;
    int i;

    i = 0;
    len = 0;

    tmp = (*lexer)->next;
    while (tmp && tmp->token == word)
    {
        len++;
        tmp = tmp->next;
    }
    cmds->out_file = malloc((len + 1) * sizeof(char *));
    if (!cmds->out_file)
        return NULL;
    (*lexer) = (*lexer)->next;
    while (i < len)
    {
        cmds->out_file[i] = ft_strdup((*lexer)->str);
        i++;
        (*lexer) = (*lexer)->next;
    }
    cmds->out_file[i] = NULL;
    return NULL;
}
void *save_in_files(t_lexer **lexer, t_simple_cmds *cmds)
{
    t_lexer *tmp;
    int len;
    int i;

    i = 0;
    len = 0;

    tmp = (*lexer)->next;
    while (tmp && tmp->token == word)
    {
        len++;
        tmp = tmp->next;
    }
    cmds->in_file = malloc((len + 1) * sizeof(char *));
    if (!cmds->in_file)
        return NULL;
    (*lexer) = (*lexer)->next;
    while (i < len)
    {
        cmds->in_file[i] = ft_strdup((*lexer)->str);
        i++;
        (*lexer) = (*lexer)->next;
    }
    cmds->in_file[i] = NULL;
    return NULL;
}
void *save_args(t_lexer **lexer, t_simple_cmds *cmds)
{
    t_lexer *tmp;
    int len;
    int i;

    i = 0;
    len = 0;
    tmp = *lexer;
    while (tmp && tmp->token == word)
    {
        len++;
        tmp = tmp->next;
    }
    cmds->args = malloc((len + 1) * sizeof(char *));
    if (!cmds->args)
        return NULL;
    while (i < len)
    {
        cmds->args[i] = ft_strdup((*lexer)->str);
        (*lexer) = (*lexer)->next;
        i++;
    }
    cmds->args[i] = NULL;
    return NULL;
}
void init_arrays(t_simple_cmds *cmds)
{
    if (cmds)
    {
        cmds->args = NULL;
        cmds->in_file = NULL;
        cmds->out_file = NULL;
        cmds->heredoc = NULL;
        cmds->aout_file = NULL;
    }
}
void *parser(t_lexer **lexer, t_simple_cmds **cmds)
{
    int i;
    int j;
    int n_pipe;
    t_lexer *tmp;

    tmp = *lexer;
    i = 0;
    n_pipe = get_numof_pipes(*lexer);
    *cmds = malloc((n_pipe + 2) * sizeof(t_simple_cmds));
    if (!cmds)
        return NULL;
    while (tmp && i <= n_pipe)
    {
        j = 0;
        init_arrays(cmds[i]);
        while (tmp && tmp->token != mpipe)
        {
            if (j == 0 && tmp->token == word)
            {
                cmds[i]->cmd = ft_strdup(tmp->str);
                tmp = tmp->next;
            }
            else if (tmp->token == word)
                save_args(&tmp, cmds[i]);
            if(tmp && tmp->token == redirect_in)
                save_in_files(&tmp, cmds[i]);
            else if(tmp && tmp->token == redirect_out)
                save_out_files(&tmp, cmds[i]);
            else if(tmp && tmp->token == heredoc)
                save_heredoc(&tmp, cmds[i]);
            else if(tmp && tmp->token == redirect_app)
                save_app_files(&tmp, cmds[i]);
            if(tmp && tmp->token == mpipe)
            {
                tmp = tmp->next;
                break;
            }
            j++;
        }
        i++;
    }
    cmds[i] = NULL;
    return *cmds;
}
// void *parser(t_lexer **lexer)
// {
//     int i;
//     int j;
//     int n_pipe;
//     t_lexer *tmp;
//     t_simple_cmds **cmds;

//     tmp = *lexer;
//     i = 0;
//     n_pipe = get_numof_pipes(*lexer);
//     cmds = malloc((n_pipe + 2) * sizeof(t_simple_cmds *)); // Ensure enough space for cmds array
//     if (!cmds)
//         return NULL;
//     while (tmp && i <= n_pipe)
//     {
//         j = 0;
//         cmds[i] = malloc(sizeof(t_simple_cmds)); // Allocate memory for each t_simple_cmds struct
//         if (!cmds[i])
//             return NULL;
//         init_arrays(cmds[i]); // Initialize each cmds element
//         while (tmp && tmp->token != mpipe)
//         {
//             if (j == 0 && tmp->token == word)
//             {
//                 (*cmds)[i].cmd = ft_strdup(tmp->str);
//                 tmp = tmp->next;
//             }
//             else if (tmp->token == word)
//                 save_args(&tmp, cmds[i]);
//             else if (tmp->token == redirect_in)
//                 save_in_files(&tmp, cmds[i]);
//             else if (tmp->token == redirect_out)
//                 save_out_files(&tmp, cmds[i]);
//             else if (tmp->token == heredoc)
//                 save_heredoc(&tmp, cmds[i]);
//             else if (tmp->token == redirect_app)
//                 save_app_files(&tmp, cmds[i]);
//             if (tmp && tmp->token == mpipe)
//             {
//                 tmp = tmp->next;
//                 break;
//             }
//             j++;
//         }
//         i++;
//     }
//     cmds[i] = NULL;
//     return cmds;
// }