#include "minishell.h"

int is_real_char(char c)
{
    return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
int allocate_for_expand(char *str)
{
    int i;
    int len;

    len = 0;
    i = 0;
    while (str[i])
    {
        if(str[i] == '$')
        {
            while (is_real_char(str[++i]))
                len++;
        }
        i++;
    }
    return len;
}
char *expand_str(char *str)
{
    int i;
    int j;
    int len;
    char *new_s;
    char *result;

    i = 0;
    j = 1;
    len = allocate_for_expand(str);
    new_s = malloc(len + 1);
    if(!new_s)
        return NULL;
    while (i < len)
        new_s[i++] = str[j++];
    result = getenv(new_s);
    result = ft_strjoin(result, str + (len + 1));
    return result;
}
void handel_expanding(char **res)
{
    int i;
    char *tmp;

    i = 0;
    while (res[i])
    {
        tmp = expand_str(res[i]);
        if(tmp)
            res[i] = tmp;
        printf("%s", res[i]);
        free(tmp);
        i++;
    }
    
}