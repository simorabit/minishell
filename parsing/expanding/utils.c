#include "../../minishell.h"

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
