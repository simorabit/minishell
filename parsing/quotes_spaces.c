/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:08:38 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/14 01:21:39 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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
			if (i != 0 && !is_withspaces(line[i - 1]))
				counter++;
			if (is_redir_has_found(line[i + 1]) && line[i] == line[i + 1] 
				&& (line[i] == '>' || line[i] == '<'))
				i++;
			else
				counter++;
			if (line[i + 1] && !is_withspaces(line[i + 1]))
				counter++;
		}
		i++;
	}
	return (counter);
}

void	redir_founded(char *line, char *new_value, int *i, int *j)
{
	int	need_space;

	need_space = 0;
	if (*i != 0 && !is_withspaces(line[*i - 1]))
	{
		new_value[*j] = ' ';
		new_value[*j + 1] = line[*i];
		(*j)++;
		need_space = 1;
	}
	if (line[*i] == '<' && line[*i + 1] == '<')
		set_redir(new_value, j, i, line[*i]);
	else if (line[*i] == '>' && line[*i + 1] == '>')
		set_redir(new_value, j, i, line[*i]);
	if (line[*i + 1] && !is_withspaces(line[*i + 1]))
	{
		new_value[*j] = line[*i];
		(*j)++;
		new_value[*j] = ' ';
		need_space = 1;
	}
	if (!need_space)
		new_value[*j] = line[*i];
}

void	*add_spaces(char *line)
{
	int		i;
	int		j;
	int		len;
	char	*new_value;

	i = 0;
	j = 0;
	len = count_redir(line);
	if (len == 0)
		return (line);
	len = ft_strlen(line) + 1 + len;
	new_value = malloc(len * sizeof(char));
	if (!new_value)
		allocation_error(line);
	while (j < len - 1)
	{
		if (is_redir_has_found(line[i]))
			redir_founded(line, new_value, &i, &j);
		else
			new_value[j] = line[i];
		i++;
		j++;
	}
	new_value[j] = '\0';
	return (new_value);
}
