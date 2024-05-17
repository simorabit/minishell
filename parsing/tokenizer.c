/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:19:15 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/15 19:21:44 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(char **res, t_lexer **lexer)
{
	int		i;
	t_lexer	*node;

	i = 0;
	while (res[i])
	{
		node = ft_lstnew(i);
        // if(check_quotes())
		if (!ft_strcmp(res[i], ">>"))
			node->token = redirect_app;
		else if (!ft_strcmp(res[i], "|"))
			node->token = mpipe;
		else if (!ft_strcmp(res[i], ">"))
			node->token = redirect_in;
		else if (!ft_strcmp(res[i], "<"))
			node->token = redirect_out;
		else if (!ft_strcmp(res[i], "<<"))
			node->token = heredoc;
		else
			node->token = word;
		node->str = res[i];
		ft_lstadd_back(lexer, node);
		i++;
	}
}
