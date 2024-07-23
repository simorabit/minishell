/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mal-mora <mal-mora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 22:14:56 by mal-mora          #+#    #+#             */
/*   Updated: 2024/07/23 06:35:48 by mal-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_real_char(char c)
{
	return ((c >= '0' && c <= '9') || \
		(c >= 'a' && c <= 'z') || \
			(c >= 'A' && c <= 'Z') || c == '_' || c == '?');
}
int is_number (char c)
{
	return (c >= '0' && c <= '9');
}
int	end_of_proccessing(char c)
{
	return (c == '$' || c == DOUBLE_QUOTE || c == SINGLE_QUOTE || c == '\0');
}

int	get_len_ep(char *s)
{
	int	len;

	len = 0;
	while (s[len] && !end_of_proccessing(s[len]))
		len++;
	return (len);
}
