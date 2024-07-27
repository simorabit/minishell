/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addresses_collector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 20:26:41 by souaouri          #+#    #+#             */
/*   Updated: 2024/07/27 04:55:18 by souaouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	garb_add(t_c_addresses **lst, t_c_addresses *new)
{
	t_c_addresses	*lastone;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	lastone = *lst;
	while (lastone->next)
		lastone = lastone->next;
	lastone->next = new;
	new->next = NULL;
}

static t_c_addresses	*garb_new(void *addrress)
{
	t_c_addresses	*newnode;

	newnode = malloc(sizeof(t_c_addresses));
	if (newnode == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	newnode->adr = addrress;
	newnode->next = NULL;
	return (newnode);
}

void	*my_alloc(size_t size)
{
	static t_c_addresses	*gooper;
	t_c_addresses			*node;
	void					*address;

	address = malloc(size);
	if (!address)
		(perror("malloc"), exit(1));
	if (gooper == NULL)
		gooper = garb_new(address);
	else
	{
		node = garb_new(address);
		garb_add(&gooper, node);
	}
	return (address);
}
