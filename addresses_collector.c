/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addresses_collector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaouri <souaouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:36:26 by oelharbi          #+#    #+#             */
/*   Updated: 2024/07/21 18:36:39 by souaouri         ###   ########.fr       */
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

static void	free_garb_list(t_c_addresses **head)
{
	t_c_addresses	*current;
	t_c_addresses	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->adr);
		current->adr = NULL;
		current = next;
	}
}

void	*my_alloc(size_t size, int flag)
{
	static t_c_addresses	*gooper;
	t_c_addresses			*node;
	void				*address;

	address = NULL;
	if (flag == 'a')
	{
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
	}
	else if (flag == 'f')
		free_garb_list(&gooper);
	return (address);
}
