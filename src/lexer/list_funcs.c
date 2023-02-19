/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:52:50 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/19 15:16:15 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

t_token	*token_new(char *str, char type)
{
	t_token	*new;

	new = xmalloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = str;
	new->type = type;
	new->next = NULL;
	return (new);
}

t_token	*token_last(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	token_add_back(t_token **lst, t_token *new_elem)
{
	t_token	*tmp;

	if (!(*lst))
	{
		*lst = new_elem;
		return ;
	}
	tmp = token_last(*lst);
	tmp->next = new_elem;
}