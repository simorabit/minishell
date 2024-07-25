/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:11:41 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/25 11:41:33 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*save_args(t_lexer **lexer, t_simple_cmds *cmds)
{
	t_lexer	*tmp;
	int		len;
	int		i;

	i = 0;
	len = 0;
	tmp = *lexer;
	while (tmp && tmp->token == word)
	{
		len++;
		tmp = tmp->next;
	}
	cmds->args = my_alloc((len + 1) * sizeof(char *));
	if (!cmds->args)
		return (NULL);
	while (i < len)
	{
		cmds->args[i] = ft_strdup((*lexer)->str);
		(*lexer) = (*lexer)->next;
		i++;
	}
	cmds->args[i] = NULL;
	return (lexer);
}

int	handel_files(t_lexer **tmp, t_simple_cmds *cmds)
{
	int	res;

	res = 0;
	if (*tmp && (*tmp)->token == redirect_in)
		cmds->in_file = open_files(tmp, redirect_in);
	else if (*tmp && (*tmp)->token == redirect_out)
		cmds->out_file = open_files(tmp, redirect_out);
	else if (*tmp && (*tmp)->token == heredoc)
	{
		res = save_heredoc(tmp, &cmds);
		if (res == -2)
			return (-1);
		cmds->heredoc = res;
	}
	else if (*tmp && (*tmp)->token == redirect_app)
		cmds->aout_file = open_files(tmp, redirect_app);
	return (res);
}

void	*handel_cmd(t_lexer **tmp, t_simple_cmds *cmds, int *j)
{
	if ((*j == 0 && (*tmp)->token == word) || 
		((*tmp)->token == word && (*tmp)->prev->token != word))
	{
		cmds->cmd = ft_strdup((*tmp)->str);
		if (!cmds->cmd)
			return (NULL);
		(*tmp) = (*tmp)->next;
	}
	else if ((*tmp)->token == word)
	{
		if (save_args(tmp, cmds) == NULL)
			return (NULL);
	}
	return (cmds);
}

t_simple_cmds	*get_node_parse(t_lexer **tmp)
{
	int				j;
	t_simple_cmds	*node;

	j = 0;
	node = ft_lstnew_cmd();
	init_arrays(node);
	while (*tmp && (*tmp)->token != mpipe)
	{
		if (!handel_cmd(tmp, node, &j))
			return (NULL);
		if (handel_files(tmp, node) == -1)
			return (NULL);
		if (*tmp && (*tmp)->token == mpipe)
		{
			*tmp = (*tmp)->next;
			break ;
		}
		j++;
	}
	return (node);
}

void	*parser(t_lexer **lexer, t_simple_cmds **cmds, int len)
{
	int				i;
	t_lexer			*tmp;
	t_simple_cmds	*node;

	node = *cmds;
	tmp = *lexer;
	i = 0;
	while (tmp && i <= len)
	{
		node = get_node_parse(&tmp);
		if (!node)
			return (NULL);
		ft_lstadd_back_cmd(cmds, node);
		i++;
	}
	return (*cmds);
}
