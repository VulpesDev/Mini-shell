/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:53:50 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/02 14:34:43 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	init_vars(char **set, int splitter[], int quot[], Token **r)
{
	*r = 0;
	*set = " \f\r\v\n\t\0";
	splitter[0] = 0;
	splitter[1] = 0;
	quot[0] = 0;
	quot[1] = 0;
}

void	check_quot(int quot[], char c)
{
	if (c == '\'' && !quot[1])
		quot[0] = !quot[0];
	else if (c == '\"' && !quot[0])
		quot[1] = !quot[1];
}

void	add_cur_token(Token **result, Token *single, int splitter[])
{
	token_add_back(result, token_create(ft_strncpy(&single->word[splitter[0]],
				splitter[1] - splitter[0])));
}

void	increment(int splitter[])
{
	splitter[1]++;
	splitter[2] = 1;
}
