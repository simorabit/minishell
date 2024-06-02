#include "../minishell.h"

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
int get_len_before_q(char *s, int *pos)
{
	int num_q;
	int len;

	len = 0;
	num_q = quotes_len(s);
	while (s[len])
	{
		if (s[len] == DOUBLE_QUOTE)
			num_q--;
		if (num_q == 0)
			break;
		len++;
		(*pos)++;
	}
	return len;
}
int get_len_end(char *s, int *i)
{
	int len;

	len = 0;
	while (s[*i] && s[*i] != '$')
	{
		(*i)++;
		len++;
	}
	return len;
}
char *handel_expand_dq(char *s, int *pos)
{
	int i;
	int len;
	char *f_str;
	char *result;
	int coun;

	coun = 0;
	i = 0;
	// while (s[i] && s[i] != '$')
	// {
	// 	if (s[i] == SINGLE_QUOTE)
	// 		coun++;
	// 	i++;
	// }

	// if (coun == 2)
	// 	return ft_strdup(s);
	i = 0;
	coun = 0;
	len = get_len_before_q(s, pos);
	while (s[++len] && s[len] != DOUBLE_QUOTE)
		(*pos)++;
	while (s[i] && s[i] != '$')
		i++;
	f_str = ft_substr(s, 0, i);
	while (s[i])
	{
		if (!coun)
			result = ft_strjoin(f_str, alloc_exp(s + (++i), &i));
		else
			result = ft_strjoin(result, alloc_exp(s + (++i), &i));
		result = ft_strjoin(result, ft_substr(s, i, get_len_end(s, &i)));
		coun++;
		(*pos)++;
	}
	return result;
}
