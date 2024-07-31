
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:19:15 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/26 14:49:26 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_cmd(t_lexer *node)
{
	t_lexer	*newnode;

	newnode = node;
	while (newnode)
	{
		if (newnode->token == word)
			return (1);
		newnode = newnode->prev;
	}
	return (0);
}

void	found_pipe( t_lexer **node, int *is_hdc, int *is_file)
{
	(*node)->token = mpipe;
	*is_hdc = 0;
	*is_file = 0;
}

void handel_red(t_lexer **node,int **is_file)
{
	if (**is_file == 1)
	{
		(*node)->token = in_file;
		if (!has_cmd((*node)) && ((*node)->prev && (*node)->prev->token == in_file))
		{
			(*node)->token = word;
			**is_file = 0;
		}
		else if((*node)->prev->token != in_file && (*node)->prev->token != redirect_in)
			**is_file = 0;
	}
	else if (**is_file == 2)
	{
		(*node)->token = out_file;
		if (!has_cmd((*node)) && ((*node)->prev && (*node)->prev->token == out_file))
			(*node)->token = word;
	}
	else if (**is_file == 3)
	{
		(*node)->token = append_out;
		if (!has_cmd((*node)) && ((*node)->prev && (*node)->prev->token == append_out))
			(*node)->token = word;
	}
}

void	check_redir(char *res, t_lexer *node, int *is_hdc, int *is_file)
{
	if (!ft_strcmp(res, ">>"))
		node->token = redirect_app;
	else if (!ft_strcmp(res, ">"))
		node->token = redirect_out;
	else if (!ft_strcmp(res, "<"))
		node->token = redirect_in;
	else if (!ft_strcmp(res, "<<"))
	{
		node->token = heredoc;
		*is_hdc = 1;
	}
	else if (*is_hdc == 1)
	{
		node->token = delimiter;
		if (!has_cmd(node) && (node->prev && node->prev->token == delimiter))
		{
			node->token = word;
			*is_file = 0;
		}
		else if((node->prev && node->prev->token == delimiter))
		{
			node->token = in_file;
			*is_hdc = 0;
		}
	}
	else if(*is_file > 0)
		handel_red(&node, &is_file);
	else
		node->token = word;
}

void	tokenizer(char **res, t_lexer **lexer)
{
	int		i;
	int		is_heredoc;
	int		is_file;
	t_lexer	*node;

	is_heredoc = 0;
	is_file = 0;
	i = 0;
	while (res[i])
	{
		node = ft_lstnew(i);
		node->str = res[i];
		ft_lstadd_back(lexer, node);
		check_redir(res[i], node, &is_heredoc, &is_file);
		if (!ft_strcmp(res[i], "<"))
			is_file = 1;
		else if (!ft_strcmp(res[i], ">"))
			is_file = 2;
		else if (!ft_strcmp(res[i], ">>"))
			is_file = 3;
		else if (!ft_strcmp(res[i], "|"))
			found_pipe(&node, &is_heredoc, &is_file);
		node->expanded = 0;
		i++;
	}
}
