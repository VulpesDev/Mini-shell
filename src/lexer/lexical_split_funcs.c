/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_split_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:25:07 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/21 13:23:59 by tvasilev         ###   ########.fr       */
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

static void	set_quotes(char *s, int i_s[], int quot[])
{
	if (s[i_s[0]] == '\'' && !quot[1])
		quot[0] = !quot[0];
	else if (s[i_s[0]] == '\"' && !quot[0])
		quot[1] = !quot[1];
}

void	split_spaces(char *s, char **result)
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
			while ((!ft_isspace(s[i_s[0]]) || quot[1] || quot[0]) && s[i_s[0]])
			{
				set_quotes(s, i_s, quot);
				result[count][i_s[1]++] = s[i_s[0]];
				i_s[0]++;
			}
			result[count++][i_s[1]] = '\0';
		}
	}	
	result[count] = 0;
}
