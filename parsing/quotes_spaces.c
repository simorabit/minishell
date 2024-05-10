#include "minishell.h"

int count_redir(char *line)
{
    int i;
    int counter;

    counter = 0;
    i = 0;
    while (line[i])
    {
        if (is_redir_has_found(line[i]))
        {
            if (is_redir_has_found(line[i + 1]))
                i++;
            counter += 2;
        }
        i++;
    }
    return counter;
}
void redir_founded(char *line, char *new_value, int *i, int *j)
{
    new_value[*j] = ' ';
    new_value[*j + 1] = line[*i];
    if (line[*i + 1] == '<')
        set_redir(new_value, j, i, '<');
    else if (line[*i + 1] == '>')
        set_redir(new_value, j, i, '>');
    else
    {
        new_value[*j + 2] = ' ';
        (*j) += 2;
    }
}
void *add_spaces(char *line)
{
    int i;
    int j;
    int len;
    char *new_value;

    i = -1;
    j = 0;
    len = ft_strlen(line) + 1 + count_redir(line);
    new_value = (char *)malloc(len * sizeof(char));
    if (!new_value)
        allocation_error(line);
    while (++i < len)
    {
        if (is_redir_has_found(line[i]))
            redir_founded(line, new_value, &i, &j);
        else
            new_value[j] = line[i];
        j++;
    }
    new_value[j] = '\0';
    free(line);
    return new_value;
}
