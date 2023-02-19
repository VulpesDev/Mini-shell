/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:25:07 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/19 11:55:22 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	allocate_word(int ii, char **word, char *s)
{
	int	length;
	int	quot[2];

	length = 0;
	quot[0] = 0;
	quot[1] = 0;
	while (s[ii] && (s[ii] != ' ' || quot[0] || quot[1]))
	{
		if (s[ii] == 39 && !quot[1])
			quot[0] = !quot[0];
		else if (s[ii] == 34 && !quot[0])
			quot[1] = !quot[1];
		ii++;
		length++;
	}
	*word = xmalloc(length * sizeof(char) + 1);
}

static void	set_vars(int *count, int i_s[], int quot[])
{
	*count = 0;
	i_s[0] = -1;
	quot[0] = 0;
	quot[1] = 0;
}

static void	helper(char *s, char c, char **result)
{
	int	count;
	int	len;
	int	i_s[2];
	int	quot[2];

	len = ft_strlen(s);
	set_vars(&count, i_s, quot);
	while (++i_s[0] < len)
	{
		if (s[i_s[0]] != c)
		{
			i_s[1] = 0;
			allocate_word(i_s[0], &result[count], s);
			while ((s[i_s[0]] != c || quot[1] || quot[0]) && s[i_s[0]])
			{
				if (s[i_s[0]] == 39 && !quot[1])
					quot[0] = !quot[0];
				else if (s[i_s[0]] == 34 && !quot[0])
					quot[1] = !quot[1];
				result[count][i_s[1]++] = s[i_s[0]];
				i_s[0]++;
			}
			result[count++][i_s[1]] = '\0';
		}
	}	
	result[count] = 0;
}

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
