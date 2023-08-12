/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:55:17 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/21 15:27:00 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include <stdio.h>

Token	*token_copy(Token *tok)
{
	Token	*copy;

	copy = xmalloc(sizeof(Token));
	copy->type = tok->type;
	copy->word = ft_strdup(tok->word);
	copy->next = NULL;
	return (copy);
}

Token	*token_create(void *content)
{
	Token	*new;

	new = xmalloc(sizeof(Token));
	if (!new)
		return (NULL);
	new->word = content;
	new->next = NULL;
	return (new);
}

Token	*token_last(Token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	token_add_back(Token **lst, Token *new_elem)
{
	Token	*tmp;

	if (!(*lst))
	{
		*lst = new_elem;
		return ;
	}
	tmp = token_last(*lst);
	tmp->next = new_elem;
}

void	token_free(Token *tok)
{
	Token	*prev;

	while (tok)
	{
		prev = tok;
		free(tok->word);
		tok = tok->next;
		free(prev);
	}
}
