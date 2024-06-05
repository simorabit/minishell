#include "../minishell.h"
char *handel_singleq(char *result, char *s, int *i, int *j)
{
	int k;

	k = ++(*i);
	while (s[*i])
	{
		if (s[*i] == SINGLE_QUOTE)
		{
			result = ft_strjoin(result, ft_substr(s, k, *j));
			break;
		}
		(*j)++;
		(*i)++;
	}
	return result;
}
char *handel_double_q(char *result, char *s, int *i, int *j)
{
	int k;
	char *res;

	k = ++(*i);
	while (s[*i])
	{

		if (s[*i] == DOUBLE_QUOTE)
		{
			res = ft_substr(s, k, *j);
			if(!res)
				return NULL;
			result = ft_strjoin(result, res);
			if (str_chr(res, '$') != -1)
				result = expand_str(res);
			break;
		}
		(*j)++;
		(*i)++;
	}
	return result;
}



