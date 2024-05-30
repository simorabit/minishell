#include "../minishell.h"

int is_real_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}
int end_of_proccessing(char c)
{
	return (c == '$' || c == DOUBLE_QUOTE || c == SINGLE_QUOTE || c == '\0');
}
int get_len_ep(char *s)
{
	int len;
	
	len = 0;
	while (s[len] && !end_of_proccessing(s[len]))
		len++;
	return len;
}
int get_sq_len(char *s)
{
	int counter;
	int i;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if(s[i] == SINGLE_QUOTE)
			counter++;
		i++;
	}
	return counter;
}
char *handel_singleq(char *s, int *pos)
{
	char *res;
	int len;
	int i;
	int s_quote;
	
	i = 0;
	len = 0;
	s_quote = get_sq_len(s);
	while (s[i])
	{
		if(s[i] == SINGLE_QUOTE)
			s_quote--;
		if(s[i] == SINGLE_QUOTE && s_quote == 0)
			break;
		len++;
		(*pos)++;
		i++;
	}
	res = ft_substr(s, 0, len);
	i = 0;
	// while (s[i++] != SINGLE_QUOTE)
	// 	(*pos)++;
	return res;
}

void *if_single_q(char *s, int *i, char *result)
{
	int len;
	char *new_str;
	int index;
	char *res;

	index = *i + 1;
	len = 0;
	while (!end_of_proccessing(s[++(*i)]))
		len++;
	new_str = ft_substr(s, index, len);
	res = ft_strjoin(result, new_str);
	free(new_str);
	
	return res;
}