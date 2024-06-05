#include "minishell.h"

int has_quotes(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == DOUBLE_QUOTE)
			return 1;
		else if (s[i] == SINGLE_QUOTE)
			return 2;
		i++;
	}
	return 0;
}
int get_mlen(char *s, char q)
{
    int i;
    int len;

    len = 0;
    i = 0;
    while (s[i])
	{
		if (s[i] != q)
			len++;
		i++;
	}
    return len;
}
void *remove_each_one(char *s, char q)
{
	int len;
	int i;
	char *new_s;
	int j;

	j = 0;
	i = 0;
	len = get_mlen(s, q);
	new_s = malloc(len + 1);
	if(!new_s)
		return NULL;
	i = 0;
	while(s[i] && j < len)
    {
        if(s[i]!= q)
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
		if (has_quotes(tmp->str) == 1 && !tmp->expanded)
			tmp->str = remove_each_one(tmp->str, DOUBLE_QUOTE);
		else if (has_quotes(tmp->str) == 2 && !tmp->expanded)
			tmp->str = remove_each_one(tmp->str, SINGLE_QUOTE);
		tmp = tmp->next;
	}
}