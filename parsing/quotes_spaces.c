/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:08:38 by mal-mora          #+#    #+#             */
/*   Updated: 2024/06/05 21:38:54 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_quotes(char *line, int i)
{
	if (i != 0 && (line[i] == DOUBLE_QUOTE || line[i] == SINGLE_QUOTE))
		return (1);
	return (0);
}
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
			if(i != 0 && !is_withspaces(line[i - 1]) && !no_quotes(line, i - 1))
				counter++;
			if (is_redir_has_found(line[i + 1]))
				i++;
			if(line[i + 1] && !is_withspaces(line[i + 1]) && !no_quotes(line, i + 1))
				counter++;
		}
		i++;
	}
	return (counter);
}

void	redir_founded(char *line, char *new_value, int *i, int *j)
{
	if (*i != 0 && !is_withspaces(line[*i - 1]) && !no_quotes(line, *i - 1))
	{
		new_value[*j] = ' ';
		new_value[*j + 1] = line[*i];
		(*j)++;
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
		set_redir(new_value, j, i, line[*i]);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		set_redir(new_value, j, i, line[*i]);
	if (line[*i + 1] && !is_withspaces(line[*i + 1]) && !no_quotes(line, *i + 1))
	{
		new_value[*j] = line[*i];
		(*j)++;
		new_value[*j] = ' ';
	}
}



void	*add_spaces(char *line)
{
	int		i;
	int		j;
	int		len;
	int		count_re;
	char	*new_value;

	i = 0;
	j = 0;
	count_re = count_redir(line);
	if(count_re == 0)
		return line;
	len = ft_strlen(line) + 1 + count_redir(line);
	new_value = malloc(len * sizeof(char));
	if (!new_value)
		allocation_error(line);
	while (j < len)
	{
		if (is_redir_has_found(line[i]))
			redir_founded(line, new_value, &i, &j);
		else
		{
			new_value[j] = line[i];
		}
		i++;
		j++;
	}
	new_value[j] = '\0';
	free(line);
	return (new_value);
}
