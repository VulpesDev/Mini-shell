/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:31:25 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/17 13:02:48 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*token_new(void *str, int type)
{
	t_token	*new;

	new = xmalloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}

void	lexer(char *str)
{
	char	**result;
	char	**result2;
	char	*set;
	int		i;
	int		k;

	set = ft_strdup("<>|&()");
	result = lexical_split(str, ' ');
	i = -1;
	while (result[++i])
	{
		result2 = symbolical_split(result[i], set);
		k = -1;
		while (result2[++k])
		{
			ft_printf("%d:%s\n", k, result2[k]);
		}
	}
	free(set);
	free(result);
	free(result2);
}
