/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:08:38 by mal-mora          #+#    #+#             */
/*   Updated: 2024/05/16 10:57:05 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redir(char *line)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (line[i])
	{
		if (is_redir_has_found(line[i]))
		{
			if (is_redir_has_found(line[i + 1]))
				i++;
			counter += 2;
		}
		i++;
	}
	return (counter);
}

void	redir_founded(char *line, char *new_value, int *i, int *j)
{
	new_value[*j] = ' ';
	new_value[*j + 1] = line[*i];
	if (line[*i] == '<' && line[*i + 1] == '<')
		set_redir(new_value, j, i, '<');
	else if (line[*i] == '>' && line[*i + 1] == '>')
		set_redir(new_value, j, i, '>');
	else
	{
		new_value[*j + 2] = ' ';
		(*j) += 2;
	}
}

int	no_quotes(char *line, int i)
{
	if (i != 0 && (line[i - 1] == SINGLE_QUOTE || line[i - 1] == DOUBLE_QUOTE))
		return (0);
	return (1);
}

void	*add_spaces(char *line)
{
	int		i;
	int		j;
	int		len;
	char	*new_value;

	i = -1;
	j = 0;
	len = ft_strlen(line) + 1 + count_redir(line);
	new_value = (char *)malloc(len * sizeof(char));
	if (!new_value)
		allocation_error(line);
	while (++i < len)
	{
		if (is_redir_has_found(line[i]) && no_quotes(line, i))
			redir_founded(line, new_value, &i, &j);
		else
			new_value[j] = line[i];
		j++;
	}
	new_value[j] = '\0';
	free(line);
	return (new_value);
}
