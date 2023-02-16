/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:25:07 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/16 17:26:34 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	allocate_word(int ii, char **word, char *s, int quot[])
{
	int	length;

	length = 0;
	while ((s[ii] != ' ' || quot[1] || quot[0]) && s[ii] && ++length)
		ii++;
	*word = xmalloc(length * sizeof(char) + 1);
}

static void	set_vars(int *count, int i_s[], int quot[])
{
	*count = 0;
	i_s[0] = -1;
	quot[0] = 0;
	quot[1] = 0;
}

void	helper(char *s, char c, char **result)
{
	int	count;
	int	i_s[2];
	int	quot[2];

	set_vars(&count, i_s, quot);
	while (s[++i_s[0]])
	{
		if (s[i_s[0]] != c)
		{
			i_s[1] = 0;
			allocate_word(i_s[0], &result[count], s, quot);
			while ((s[i_s[0]] != c || quot[1] || quot[0]) && s[i_s[0]])
			{
				if (s[i_s[0]] == 39 && !quot[1])
					quot[0] = !quot[0];
				else if (s[i_s[0]] == 34 && !quot[0])
					quot[1] = !quot[1];
				else
					result[count][i_s[1]++] = s[i_s[0]];
				i_s[0]++;
			}
			result[count++][i_s[1]] = '\0';
		}
	}	
	result[count] = 0;
}