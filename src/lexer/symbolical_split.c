/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbolical_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:26:57 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/21 11:45:42 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static unsigned int	occ_c(char *s, char *c)
{
	int	i;
	int	result;
	int	quot[2];

	i = 0;
	result = 1;
	if (s == NULL)
		return (0);
	quot[0] = 0;
	quot[1] = 0;
	while (s[i])
	{
		if (s[i] == 39 && !quot[1])
			quot[0] = !quot[0];
		else if (s[i] == 34 && !quot[0])
			quot[1] = !quot[1];
		if (ft_strchr(c, s[i]) && !quot[0] && !quot[1])
			result++;
		i++;
	}
	return (result);
}

char	**symbolical_split(char *s, char *c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = xmalloc((occ_c(s, c) + 2) * sizeof(char *));
	if (!result)
		return (NULL);
	split_symbol(s, c, result);
	return (result);
}
