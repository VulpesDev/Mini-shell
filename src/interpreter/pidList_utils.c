/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pidList_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:48:25 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/21 15:59:21 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"

PidList	*pidList_create(int pid)
{
	PidList	*new;

	new = xmalloc(sizeof(PidList));
	if (!new)
		return (NULL);
	new->pid = pid;
	new->next = NULL;
	return (new);
}

PidList	*pidList_last(PidList *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	pidList_add(PidList **lst, PidList *new_elem)
{
	PidList	*tmp;

	if (!(*lst))
	{
		*lst = new_elem;
		return ;
	}
	tmp = pidList_last(*lst);
	tmp->next = new_elem;
}

void	pidList_clear(PidList **cur)
{
	PidList *prev;

	if (*cur == NULL)
		return ;
	while (*cur)
	{
		prev = *cur;
		*cur = (*cur)->next;
		free(prev);
	}
}