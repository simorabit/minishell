/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes_spaces.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:14:39 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/22 06:05:19 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	check_quotes(char *line)
{
	int i;
	int flag;
	
	i = 0;
	flag = 1;
	while (line[i])
	{
		if(line[i] == DOUBLE_QUOTE)
		{
			i++;
			flag = 0;
			while (line[i])
			{
				if(line[i] == DOUBLE_QUOTE)
				{
					flag = 1;
					break;	
				}
				i++;
			}
		}else if(line[i] == SINGLE_QUOTE)
		{
				i++;
			flag = 0;
			while (line[i])
			{
				if(line[i] == SINGLE_QUOTE)
				{
					flag = 1;
					break;	
				}
				i++;
			}
		}
		i++;
	}
	return flag;
}
int	handel_quotes(char *line)
{
	if(!check_quotes(line))
		return 0;
	return 1;
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
