/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:14:39 by mal-mora          #+#    #+#             */
/*   Updated: 2024/06/10 16:47:59 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes(char *line, char q)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == q)
			counter++;
		i++;
	}
	return (counter);
}

int	handel_quotes(char *line)
{
	if (quotes(line, SINGLE_QUOTE) % 2 == 0 && quotes(line, DOUBLE_QUOTE) % 2 == 0)
		return (1);
	error_msg(SYNTAX_ERROR);
	return (0);
}

int	is_redir_has_found(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

void	set_redir(char *s, int *j, int *i, char c)
{
	s[*j] = c;
	(*j)++;
	s[*j] = c;
	(*i)++;
}
