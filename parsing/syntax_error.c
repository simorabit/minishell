/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:24:15 by mal-mora          #+#    #+#             */
/*   Updated: 2024/06/10 16:47:38 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redirs(t_lexer *lexer)
{
	return (lexer->token >= 2 && lexer->token <= 5);
}

int	syn_err_checker(t_lexer **lexer)
{
	t_lexer	*tmp;

	tmp = *lexer;
	while (tmp)
	{
		if (is_redirs(tmp))
		{
			if (!tmp->next || is_redirs(tmp->next))
				return (0);
		}
		else if (tmp->token == mpipe)
		{
			if (!tmp->next || !tmp->prev)
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	syntax_error(t_lexer **lexer)
{
	if (!syn_err_checker(lexer))
	{
		error_msg(SYNTAX_ERROR);
		return (0);
	}
	return (1);
}
