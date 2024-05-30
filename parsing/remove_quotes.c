#include "minishell.h"

int has_quotes(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == DOUBLE_QUOTE)
			return 1;
		i++;
	}
	return 0;
}
int get_mlen(char *s)
{
    int i;
    int len;

    len = 0;
    i = 0;
    while (s[i])
	{
		if (s[i] != DOUBLE_QUOTE)
			len++;
		i++;
	}
    return len;
}
void *remove_each_one(char *s)
{
	int len;
	int i;
	char *new_s;
	int j;

	j = 0;
	i = 0;
	len = get_mlen(s);
	new_s = malloc(len + 1);
	if(!new_s)
		return NULL;
	i = 0;
	while(s[i] && j < len)
    {
        if(s[i]!= DOUBLE_QUOTE)
			new_s[j++] = s[i];
        i++;
    }
	new_s[j] = '\0';
	return new_s;
}
void remove_quotes(t_lexer **lexer)
{
	t_lexer *tmp;

	tmp = *lexer;
	while (tmp)
	{
		if (has_quotes(tmp->str))
			tmp->str = remove_each_one(tmp->str);
		tmp = tmp->next;
	}
}