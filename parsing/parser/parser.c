#include "../minishell.h"

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

void handel_files(t_lexer **tmp, t_simple_cmds *cmds)
{
    if (*tmp && (*tmp)->token == redirect_in)
        save_in_files(tmp, cmds);
    else if (*tmp && (*tmp)->token == redirect_out)
        save_out_files(tmp, cmds);
    else if (*tmp && (*tmp)->token == heredoc)
        save_heredoc(tmp, cmds);
    else if (*tmp && (*tmp)->token == redirect_app)
        save_app_files(tmp, cmds);
}

void handel_cmd(t_lexer **tmp, t_simple_cmds *cmds, int *j)
{
    if (*j == 0 && (*tmp)->token == word)
    {
        cmds->cmd = ft_strdup((*tmp)->str);
        (*tmp) = (*tmp)->next;
    }
    else if ((*tmp)->token == word)
        save_args(tmp, cmds);
}
t_simple_cmds *get_node_parse(t_lexer **tmp)
{
    int j;
    t_simple_cmds *node;

    j = 0;
    node = ft_lstnew_cmd();
    init_arrays(node);
    while (*tmp && (*tmp)->token != mpipe)
    {
        handel_cmd(tmp, node, &j);
        if (*tmp && (*tmp)->token == redirect_in)
            save_in_files(tmp, node);
        handel_files(tmp, node);
        if (*tmp && (*tmp)->token == mpipe)
        {
            *tmp = (*tmp)->next;
            break;
        }
        j++;
    }
    return node;
}


void *parser(t_lexer **lexer, t_simple_cmds **cmds, int len)
{
    int i;
    t_lexer *tmp;
    t_simple_cmds *node;

    node = *cmds;
    tmp = *lexer;
    i = 0;
    while (tmp && i <= len)
    {
        node = get_node_parse(&tmp);
        ft_lstadd_back_cmd(cmds, node);
        i++;
    }
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