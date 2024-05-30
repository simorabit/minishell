#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*new_value;

	i = 0;
	new_value = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!new_value)
		return (NULL);
	while (s1[i])
	{
		new_value[i] = s1[i];
		i++;
	}
	new_value[i] = '\0';
	return (new_value);
}
char *ft_strncpy(char *s, int len)
{
	char *new_s;
	int i;

	i = 0;
	if(!s)
		return NULL;
	new_s = malloc(len + 1);
	if (!new_s)
		return (NULL);
	while (i < len)
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return new_s;
}
int	str_chr(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
