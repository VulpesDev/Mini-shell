/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:31:25 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/16 17:26:22 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static unsigned int	occ_c(const char *s, char c)
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
		if (s[i] == c)
			in_c = 1;
		if (in_c && s[i] != c)
		{
			result++;
			in_c = 0;
		}
	}
	return (result);
}

char	**lexical_split(char *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = xmalloc((occ_c(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	helper(s, c, result);
	return (result);
}

void	lexer(char *str)
{
	char	**result;
	int		i;

	i = -1;
	result = lexical_split(str, ' ');
	while (result[++i])
	{
		ft_printf("%s\n", result[i]);
	}
}
