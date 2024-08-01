/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:24:15 by mal-mora          #+#    #+#             */
/*   Updated: 2024/08/01 17:31:38 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	handel_herdoc_err(t_lexer **lexer, t_cmds **cmds)
{
	int		len;
	char	*del;

	len = 0;
	del = NULL;
	(*lexer) = (*lexer)->next;
	while ((*lexer) && ((*lexer)->token == delimiter || \
		(*lexer)->token == heredoc))
	{
		if ((*lexer)->token == delimiter)
		{
			del = ft_strdup((*lexer)->str);
			handel_heredoc(del, cmds);
		}
		(*lexer) = (*lexer)->next;
	}
}

int	syntax_error(t_lexer **lexer, t_env **env_list)
{
	if (!syn_err_checker(lexer))
	{
		error_msg(SYNTAX_ERROR, env_list);
		return (0);
	}
	return (1);
}
