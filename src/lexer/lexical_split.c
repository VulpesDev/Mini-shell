/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:09:50 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/21 11:10:58 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

static unsigned int	occ_c(const char *s)
{
	int	i;
	int	result;
	int	in_c;

	i = -1;
	result = 0;
	in_c = 1;
	if (s == NULL)
		return (0);
	while (s[++i])
	{
		if (ft_isspace(s[i]))
			in_c = 1;
		if (in_c && !ft_isspace(s[i]))
		{
			result++;
			in_c = 0;
		}
	}
	return (result);
}

char	**lexical_split(char *s)
{
	char	**result;

	if (!s)
		return (NULL);
	result = xmalloc((occ_c(s) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	split_spaces(s, result);
	return (result);
}