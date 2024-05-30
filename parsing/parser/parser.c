#include "../minishell.h"

int redir_len(t_lexer *lexer)
{
    int i;

    i = 0;
    t_lexer *tmp;
    tmp = lexer;
    while (tmp && tmp->token != mpipe)
    {
        if (is_redirs(tmp))
        {
            while (tmp && tmp->token != mpipe)
            {
                tmp = tmp->next;
                i++;
            }
        }
        else
            tmp = tmp->next;
    }
    return i;
}
void save_redi(t_lexer *lexer, t_simple_cmds *node)
{
    t_lexer *tmp;
    t_lexer *tmp2;
    int i;
    t_lexer *new_lexer;
    tmp = lexer;
    i = 0;
    while (tmp && tmp->token != mpipe)
    {
        if (is_redirs(tmp))
        {
            while (tmp && tmp->token != mpipe)
            {
                new_lexer = ft_lstnew(i);
                new_lexer->str = tmp->str;
                new_lexer->token = tmp->token;
                tmp2 = tmp;
                tmp = tmp->next;
                ft_lst_remove(&lexer, tmp2->i);
                ft_lstadd_back(&(node->redirections), new_lexer);
                i++;
            }
        }
        else
            tmp = tmp->next;
    }
}

int has_redir(t_lexer *lexer)
{
    t_lexer *tmp;

    tmp = lexer;
    while (tmp && tmp->token != mpipe)
    {
        if (is_redirs(tmp))
            return 1;
        tmp = tmp->next;
    }
    return 0;
}
int put_data_in_node(t_simple_cmds *node, t_lexer *tmp, int len)
{
    int j;

    j = 0;
    node->str = malloc(len + 1);
    if(!node->str)
        return -1;
    while (j < len)
    {
        node->str[j] = tmp->str;
        j++;
        tmp = tmp->next;
    }
    node->str[j] = NULL;
    return 0;
}
void parser(t_lexer **lexer, t_simple_cmds **cmds)
{
    t_simple_cmds *node;
    int n_pipe;
    int i;
    t_lexer *tmp;

    tmp = *lexer;
    i = 0;
    n_pipe = get_numof_pipes(*lexer);
    while (i <= n_pipe)
    {
        node = ft_lstnew_cmd();
        if (has_redir(tmp))
            save_redi(tmp, node);
        // if(i == 1)
        // {
        //     printf("%d", ft_lstsize_new(tmp));
        //     exit(0);
        // }
        if(put_data_in_node(node, tmp, ft_lstsize_new(tmp)) == -1)
        {
            free(node);
            return ;
        }
        ft_lstadd_back_cmd(cmds, node);
        while (tmp && tmp->token != mpipe)
            tmp = tmp->next;
        if(tmp == NULL)
            break;
        else if(tmp->token == mpipe)
            tmp = tmp->next;
        i++;
    }
    // printf("%s\n", (*cmds)->redirections->str);
    print_cmd((*cmds));
    exit(0);
}