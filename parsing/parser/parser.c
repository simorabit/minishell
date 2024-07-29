/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 23:11:41 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/29 16:44:48 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*save_args(t_lexer **lexer, t_cmds *cmds)
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

int	handel_files(t_lexer **tmp, t_cmds *cmds, t_env **env)
{
	int	res;

	res = 0;
	if (*tmp && (*tmp)->token == redirect_in)
		cmds->in_file = open_files(tmp, redirect_in, &cmds, env);
	else if (*tmp && (*tmp)->token == redirect_out)
		cmds->out_file = open_files(tmp, redirect_out, &cmds, env);
	else if (*tmp && (*tmp)->token == heredoc)
	{
		res = save_heredoc(tmp, &cmds);
		if (res == -2)
			return (-1);
		cmds->heredoc = res;
	}
	else if (*tmp && (*tmp)->token == redirect_app)
		cmds->aout_file = open_files(tmp, redirect_app, &cmds, env);
	return (res);
}

void	*handel_cmd(t_lexer **tmp, t_cmds *cmds, int *j)
{
	if ((*j == 0 && (*tmp)->token == word) || \
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

t_cmds	*get_node_parse(t_lexer **tmp, t_env **env)
{
	int		j;
	t_cmds	*node;

	j = 0;
	node = ft_lstnew_cmd();
	node->is_ambugious = 0;
	init_arrays(node);
	while (tmp && *tmp && (*tmp)->token != mpipe)
	{
		if (!handel_cmd(tmp, node, &j))
			return (NULL);
		if (handel_files(tmp, node, env) == -1)
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

void	*parser(t_lexer **lexer, t_cmds **cmds, int len, t_env **env)
{
	int		i;
	t_lexer	*tmp;
	t_cmds	*node;

	node = *cmds;
	tmp = *lexer;
	i = 0;
	while (tmp && i <= len)
	{
		node = get_node_parse(&tmp, env);
		if (!node)
			return (NULL);
		ft_lstadd_back_cmd(cmds, node);
		i++;
	}
	return (*cmds);
}
