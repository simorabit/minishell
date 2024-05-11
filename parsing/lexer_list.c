/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 12:16:49 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/11 11:19:46 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

t_lexer	*ft_lstlast(t_lexer *lexer)
{
	while (lexer)
	{
		if (!lexer->next)
			return (lexer);
		lexer = lexer->next;
	}
	return (lexer);
}

t_lexer	*ft_lstnew(int content)
{
	t_lexer	*lexer;

	lexer = (t_lexer *)malloc(sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->i = content;
	lexer->next = NULL;
	lexer->prev = NULL;
	return (lexer);
}

int	ft_lstsize(t_lexer *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_lstadd_back(t_lexer **lexer, t_lexer *new)
{
	t_lexer	*last;

	if (!lexer)
		return ;
	if (*lexer)
	{
		last = ft_lstlast(*lexer);
		last->next = new;
		new->prev = last;
	}
	else
		*lexer = new;
}
