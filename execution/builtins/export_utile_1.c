/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utile_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:39:47 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/11 10:40:16 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_lstsize_env(t_env *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		i++; 
	}
	return (i);
}

// void	ft_memcpy(char *dst, char *src, size_t	n)
// {
// 	char	*d;
// 	char	*s;
// 	size_t	i;

// 	d = dst;
// 	s = src;
// 	i = 0;
// 	if (d == NULL && s == NULL)
// 		return ;
// 	while (i < n)
// 	{
// 		d[i] = s[i];
// 		i++;
// 	}
// }

char	*add_double_quotes(char *var)
{
	int		i;
	int		j;
	int		x;
	int		size;
	char	*ptr;

	size = ft_strlen(var);
	i = 0;
	j = 0;
	x = 0;
	if (ft_strchr(var, '='))
		size += 2;
	
	ptr = malloc(sizeof(char) * size + 1);
	if (var[0] == '\0' || var == NULL)
		return (NULL);
	while (var[i])
	{
		if (var[i] == '=' && x == 0)
		{
			ptr[j] = '=';
			j++;
			ptr[j] = '\"';
			j++;
			i++;
			x++;
		}
		if (var[i] != '\0')
		{
			ptr[j] = var[i];
			i++;
			j++;
		}
	}
	
	if (x != 0)
	{
		ptr[j] = '\"';
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

void	ft_sort_env(t_env *env)
{
	char	**ptr;
	char	*tmp;
	int		list_len;
	int		i;
	t_env	*head;

	ptr = NULL;
	list_len = ft_lstsize_env(env);
	i = 0;
	while (i < list_len)
	{
		head = env;
		while(head->next)
		{
			if (ft_strcmp(head->content, head->next->content) > 0)
			{
				tmp = head->content;
				head->content = head->next->content;
				head->next->content = tmp;
			}
			head = head->next;
		}
		i++;
	}
	head = NULL;
}

char	*get_var_from_beg_to_eq(char *var)
{
	int 	i;
	char	*ptr;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	ptr = malloc(i + 1);
	i = 0;
	while (var[i] && var[i + 1] != '=')
	{
		ptr[i] = var[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*get_content_from_eq_to_fin(char *var)
{
	int	i;

	i = 0;
	if (!var)
		return (NULL);
	if (ft_strchr(var, '='))
	{
		while (var[i] && var[i] != '=')
			i++;
		if (var[i] == '=')
			i++;
	}
	return (var + i);
}
