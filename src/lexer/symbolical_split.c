/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbolical_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:22:46 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/19 11:55:20 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	allocate_word(int ii, char **word, char *s, int quot[])
{
	int		length;
	char	*set;

	length = 0;
	set = ft_strdup("<>|&()");
	if (quot[0])
		while (s[ii] != 39 && s[ii] && ++length)
			ii++;
	else if (quot[1])
		while (s[ii] != 34 && s[ii] && ++length)
			ii++;
	else
		while (s[ii] && ++length)
			ii++;
	free(set);
	*word = xmalloc(length * sizeof(char) + 1);
}

static void	set_vars(int *count, int i_s[], int quot[])
{
	*count = 0;
	i_s[0] = -1;
	quot[0] = 0;
	quot[1] = 0;
}

static void	helper(char *s, char *c, char **result)
{
	int	count;
	int	len;
	int	i_s[2];
	int	quot[2];

	len = ft_strlen(s);
	set_vars(&count, i_s, quot);
	while (++i_s[0] < len)
	{
		if (!ft_strchr(c, s[i_s[0]]))
		{
			i_s[1] = 0;
			allocate_word(i_s[0], &result[count], s, quot);
			while ((!ft_strchr(c, s[i_s[0]])|| quot[1] || quot[0]) && s[i_s[0]])
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
		if (s[i_s[0]])
		{
			result[count] = xmalloc(2 * sizeof(char *));
			result[count][0] = s[i_s[0]];
			result[count++][1] = '\0';
		}
	}	
	result[count] = 0;
}

static unsigned int	occ_c(const char *s, char *c)
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
		if (ft_strchr(c, s[i]))
		{
			if (!in_c)
				result++;
			in_c = 1;
		}
		if (in_c && !ft_strchr(c, s[i]))
		{
			result++;
			in_c = 0;
		}
	}
	return (result);
}

char	**symbolical_split(char *s, char *c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = xmalloc((occ_c(s, c) + 100) * sizeof(char *));
	if (!result)
		return (NULL);
	helper(s, c, result);
	return (result);
}