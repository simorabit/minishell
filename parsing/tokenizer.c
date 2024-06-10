/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:19:15 by mal-mora          #+#    #+#             */
/*   Updated: 2024/06/10 16:47:49 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_redirections(char *res, t_lexer *node, int *is_heredoc, int *is_file)
{
	if (!ft_strcmp(res, ">>"))
		node->token = redirect_app;
	else if (!ft_strcmp(res, "|"))
	{
		node->token = mpipe;
		*is_heredoc = 0;
		*is_file = 0;
	}
	else if (!ft_strcmp(res, ">"))
		node->token = redirect_in;
	else if (!ft_strcmp(res, "<"))
		node->token = redirect_out;
	else if (!ft_strcmp(res, "<<"))
	{
		node->token = heredoc;
		*is_heredoc = 1;
	}
	else if (*is_heredoc)
		node->token = delimiter;
	else if (*is_file)
		node->token = file;
	else
		node->token = word;
}
void tokenizer(char **res, t_lexer **lexer)
{
	int i;
	t_lexer *node;
	int is_heredoc;
	int is_file;

	is_heredoc = 0;
	is_file = 0;
	i = 0;
	while (res[i])
	{
		node = ft_lstnew(i);
		check_redirections(res[i], node, &is_heredoc, &is_file);
		if ((!ft_strcmp(res[i], "<")) || (!ft_strcmp(res[i], ">")) ||
			(!ft_strcmp(res[i], ">>")))
			is_file = 1;
		node->str = res[i];
		node->expanded = 0;
		ft_lstadd_back(lexer, node);
		i++;
	}
}
