/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:48:27 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/02 15:01:39 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <string.h>

Token	*split_by_whitespace(Token single)
{
	Token	*result;
	char	*set;
	int		quot[2];
	int		splitter[2];

	init_vars(&set, splitter, quot, &result);
	while (single.word[splitter[1]])
	{
		check_quot(quot, single.word[splitter[1]]);
		if (strchr(set, single.word[splitter[1]]) && !quot[0]
			&& !quot[1])
		{
			add_cur_token(&result, &single, splitter);
			while (single.word[splitter[1]] &&
				strchr(set, single.word[splitter[1]]))
				splitter[1]++;
			splitter[0] = splitter[1];
		}
		else
			splitter[1]++;
	}
	add_cur_token(&result, &single, splitter);
	return (result);
}

char	*symbol_check(char *str)
{
	if (!ft_strncmp(str, "||", 2)
		|| !ft_strncmp(str, "&&", 2)
		|| !ft_strncmp(str, "<<", 2)
		|| !ft_strncmp(str, ">>", 2))
		return (ft_strncpy(str, 2));
	else if (!ft_strncmp(str, "|", 1)
		|| !ft_strncmp(str, "(", 1)
		|| !ft_strncmp(str, ")", 1)
		|| !ft_strncmp(str, ">", 1)
		|| !ft_strncmp(str, "<", 1))
		return (ft_strncpy(str, 1));
	return (0);
}

void	symbol_add(Token single, Token **result, int splitter[], char *check)
{
	if (splitter[1] - splitter[0])
		add_cur_token(result, &single, splitter);
	token_add_back(result, token_create(ft_strdup(check)));
	splitter[1] += ft_strlen(check);
	splitter[0] = splitter[1];
	splitter[2] = 0;
}

Token	*split_by_symbols(Token single)
{
	Token	*result;
	char	*set;
	char	*check;
	int		quot[2];
	int		splitter[3];

	init_vars(&set, splitter, quot, &result);
	splitter[2] = 0;
	check = 0;
	while (single.word[splitter[1]])
	{
		check_quot(quot, single.word[splitter[1]]);
		check = symbol_check(&single.word[splitter[1]]);
		if (check != 0 && !quot[0] && !quot[1])
			symbol_add(single, &result, splitter, check);
		else
			increment(splitter);
		free(check);
	}
	if (splitter[2])
		add_cur_token(&result, &single, splitter);
	return (result);
}
