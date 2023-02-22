/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:53:17 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/22 12:00:53 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "stdlib.h"
#include "parser.h"

void	block_clear(t_code_block **lst)
{
	t_code_block	*tmp;

	while ((*lst))
	{
		tmp = (*lst)->next;
		dp_free((*lst)->words);
		free((*lst));
		(*lst) = tmp;
	}
	*lst = NULL;
}

t_code_block	*block_new(char **words, int symbol)
{
	t_code_block	*new;

	new = xmalloc(sizeof(t_code_block));
	if (!new)
		return (NULL);
	new->words = words;
	new->symbol = symbol;
	new->next = NULL;
	return (new);
}

t_code_block	*block_last(t_code_block *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	block_add_back(t_code_block **lst, t_code_block *new_elem)
{
	t_code_block	*tmp;

	if (!(*lst))
	{
		*lst = new_elem;
		return ;
	}
	tmp = block_last(*lst);
	tmp->next = new_elem;
}
