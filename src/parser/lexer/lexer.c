/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:49:36 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/07 13:53:26 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <string.h>
#include <stdio.h>

	/*Tasks of lexer
		1. convert string to tokens
		What are the steps involed?


		Create a list
		call a "rule" on each element of the list
		in the beginning we have 1 element which is the entire command line
		we have a split function which takes a list and applies a "split" with a given
		"split rule"

		example

		cat| echo && echo "this is a string"

		1. convert into list element
		 -> "cat| echo &&echo "this is a string"" -> NULL


		3. apply other split rule which is split by symbols
		 -> cat -> pipe -> echo -> && -> echo -> "this is a string" -> NULL

		4. convert list into token list and slap labels on it

		5. return
	*/

int	split(Token **wip, Token *(*split_func)(Token))
{
	Token	*current;
	Token	*new;

	current = *wip;
	new = 0;
	while (current)
	{
		if (!new)
			new = split_func(*current);
		else
			token_last(new)->next = split_func(*current);
		current = current->next;
	}
	if (*wip)
		token_free(*wip);
	*wip = new;
	return (0);
}

Token	*split_line(char *line)
{
	Token	*current_wip;

	current_wip = token_create(line);
	split(&current_wip, split_by_whitespace);
	split(&current_wip, split_by_symbols);
	return (current_wip);
}

Token	*convert(char *line)
{
	Token	*tokens;

	tokens = split_line(line);
	return (labeling(tokens));
}

Token *lexer(char *line)
{
	Token	*tokens;

	if (!line)
		return (NULL);
	tokens = convert(line);
	return (tokens);
}
