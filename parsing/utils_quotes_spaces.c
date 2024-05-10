#include "minishell.h"

int quotes(char *line, char q)
{
    int i;
    int counter;

    counter = 0;
    i = 0;
    while (line[i])
    {
        if (line[i] == q)
            counter++;
        i++;
    }
    return counter;
}
int handel_quotes(char *line)
{
    if (quotes(line, '\'') % 2 == 0 && quotes(line, '\"') % 2 == 0)
        return 1;
    return 0;
}
int is_redir_has_found(char c)
{
    if (c == '<' || c == '>' || c == '|')
        return 1;
    return 0;
}
void set_redir(char *s, int *j, int *i, char c)
{
    s[*j + 2] = c;
    s[*j + 3] = ' ';
    (*i)++;
    (*j) += 3;
}