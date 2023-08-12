/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:36:23 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/21 15:27:00 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections.h"

t_Redirection	*redir_create(void *content, int type)
{
	t_Redirection	*new;

	new = xmalloc(sizeof(t_Redirection));
	if (!new)
		return (NULL);
	new->str = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_Redirection	*redir_last(t_Redirection *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	redir_add_back(t_Redirection **lst, t_Redirection *new_elem)
{
	t_Redirection	*tmp;

	if (!(*lst))
	{
		*lst = new_elem;
		return ;
	}
	tmp = redir_last(*lst);
	tmp->next = new_elem;
}

void	redir_free(t_Redirection *lst)
{
	t_Redirection	*prev;

	while (lst)
	{
		prev = lst;
		lst = lst->next;
		free(prev);
	}
}
