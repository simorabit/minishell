#include "minishell.h"

void allocation_error(char *s)
{
    free(s);
    printf(ErrorInAllocation);
    exit(0);
}
void error_msg(char *s)
{
    printf("%s", s);
    // exit(0);
}
void free_list(char **list)
{
    int i;

    i = 0;
    if(list == NULL)
        return;
    while (list[i])
    {
        free(list[i]);
        i++;
    }
    free(list);
}