#include "../../minishell.h"


// static void	*ft_memcpy(void	*dst, const void	*src, size_t	n)
// {
// 	unsigned char		*d;
// 	unsigned const char	*s;
// 	size_t				i;

// 	d = dst;
// 	s = src;
// 	i = 0;
// 	if (d == NULL && s == NULL)
// 		return (NULL);
// 	while (i < n)
// 	{
// 		d[i] = s[i];
// 		i++;
// 	}
// 	return (d);
// }
//TODO - we can modify this function after
// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*ptr;
// 	size_t	len_s1;
// 	size_t	len_s2;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	len_s1 = ft_strlen(s1);
// 	len_s2 = ft_strlen(s2);
// 	ptr = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
// 	if (!ptr)
// 		return (NULL);
// 	ft_memcpy(ptr, s1, len_s1);
// 	ft_memcpy (ptr + len_s1, s2, len_s2);
// 	ptr[len_s1 + len_s2] = '\0';
// 	return (ptr);
// }

char	*ft_strchr(char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (char) c)
			return (ptr);
		ptr++;
	}
	if ((char)c == '\0')
		return (ptr);
	return (NULL);
}
