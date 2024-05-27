#include "minishell.h"
int quotes_len(char *s)
{
	int i;
	int counter;

	counter = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == DOUBLE_QUOTE)
			counter++;
		i++;
	}
	return counter;
}
char *handel_expand_dq(char *s, int *pos)
{
	int num_q;
	int i;
	int len;
	char *befor_dollar;
	char *res;
	int mlen = 0;
	char *result = NULL;
	int coun;
	
	coun = 0;
	i = 0;
	len = 0;
	num_q = quotes_len(s);
	while (s[len])
	{
		if (s[len] ==  DOUBLE_QUOTE)
			num_q--;
		if (num_q == 0)
			break;
		len++;
		(*pos)++;
	}
	while(s[++len] && s[len] != DOUBLE_QUOTE)
		(*pos)++;
	
	while (s[i])
	{
		if (s[i] != '$')
			i++;
		else
			break;
	}
	befor_dollar = ft_substr(s, 0, i);
	int d;
	while (s[i])
	{
		res = allocate_for_expand(s + (++i), &i);
		if (!coun)
			result = ft_strjoin(befor_dollar, res);
		else
			result = ft_strjoin(result, res);
		d = i;
		while (s[i] && s[i] != '$')
		{
			i++;
			mlen++;
		}
		result = ft_strjoin(result, ft_substr(s, d, mlen));
		coun++;
		(*pos)++;
	}
	return result;
}