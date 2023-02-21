/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:31:25 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/21 13:22:26 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"

/*lexer takes the str passed by readline
and creates tokens out of it. The return value
is either NULL in case of error or the token list.*/
t_token	*lexer(char *str)
{
	t_token	*tokens;
	char	**r;
	char	**r2;
	char	*set;
	int		i_s[2];

	tokens = 0;
	set = ft_strdup("<>|&()");
	r = lexical_split(str);
	i_s[0] = -1;
	while (r[++i_s[0]])
	{
		r2 = symbolical_split(r[i_s[0]], set);
		i_s[1] = -1;
		while (r2[++i_s[1]])
			if (ft_strchr(set, (int)*r2[i_s[1]]))
				token_add_back(&tokens, token_new(ft_strdup(r2[i_s[1]]), 's'));
		else
			token_add_back(&tokens, token_new(ft_strdup(r2[i_s[1]]), 'w'));
		dp_free(r2);
	}
	free(set);
	dp_free(r);
	return (tokens);
}
