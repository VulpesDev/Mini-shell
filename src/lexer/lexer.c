/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:31:25 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/19 17:05:46 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token	*lexer(char *str)
{
	t_token	*tokens;
	char	**result;
	char	**result2;
	char	*set;
	int		i;
	int		k;

	tokens = 0;
	set = ft_strdup("<>|&()");
	result = lexical_split(str);
	i = -1;
	while (result[++i])
	{
		result2 = symbolical_split(result[i], set);
		//*for displaying
		k = -1;
		while (result2[++k])
			if (ft_strchr(set, (int)*result2[k]))
				token_add_back(&tokens, token_new(result2[k], 's'));
			else
				token_add_back(&tokens, token_new(result2[k], 'w'));
	}
	free(set);
	free(result);
	free(result2);
	return (tokens);
}
