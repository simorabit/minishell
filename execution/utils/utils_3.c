#include "../../minishell.h"

static char	*ft_substr_exe(char *s, unsigned int start, size_t	len)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len >= ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] && len > i)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static int	count_word(const char	*s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			j++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (j);
}

static size_t	count_len(const char	*s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

void	*free_double_ptr(char	**ptr)
{
	size_t	i;

	i = 0;
	if (ptr == NULL || ptr[i]== NULL)
		return (NULL);
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
	return (NULL);
}

char	**ft_split_exe(char *s, char c)
{
	char	**ptr;
	size_t	size;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	size = count_word(s, c);
	i = 0;
	j = 0;
	ptr = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ptr)
		return (NULL);
	while (s[j] && size--)
	{
		while (s[j] == c)
			j++;
		ptr[i] = ft_substr_exe(s, j, count_len(&s[j], c));
		if (!ptr[i])
			return (free_double_ptr(ptr), NULL);
		j += count_len(&s[j], c);
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}
