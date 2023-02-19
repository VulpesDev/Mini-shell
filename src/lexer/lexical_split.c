/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:25:07 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/19 17:45:48 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

static void	allocate_word(int ii, char **word, char *s)
{
	int	length;
	int	quot[2];

	length = 0;
	quot[0] = 0;
	quot[1] = 0;
	while (s[ii] && (!ft_isspace(s[ii]) || quot[0] || quot[1]))
	{
		if (s[ii] == '\'' && !quot[1])
			quot[0] = !quot[0];
		else if (s[ii] == '\"' && !quot[0])
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

static void	helper(char *s, char **result)
{
	int	count;
	int	len;
	int	i_s[2];
	int	quot[2];

	len = ft_strlen(s);
	set_vars(&count, i_s, quot);
	while (++i_s[0] < len)
	{
		if (!ft_isspace(s[i_s[0]]))
		{
			i_s[1] = 0;
			allocate_word(i_s[0], &result[count], s);
			while ((!ft_isspace(s[i_s[0]])|| quot[1] || quot[0]) && s[i_s[0]])
			{
				if (s[i_s[0]] == '\'' && !quot[1])
					quot[0] = !quot[0];
				else if (s[i_s[0]] == '\"' && !quot[0])
					quot[1] = !quot[1];
				result[count][i_s[1]++] = s[i_s[0]];
				i_s[0]++;
			}
			result[count++][i_s[1]] = '\0';
		}
	}	
	result[count] = 0;
}

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
	helper(s, result);
	return (result);
}
