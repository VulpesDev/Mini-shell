/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:38:06 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/22 12:16:36 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"

t_code_block	*parser(t_meta *meta, t_token *tokens)
{
	t_code_block	*blocks;
	int				symbol;
	char			**words;
	int				i;

	blocks = 0;
	while (tokens)
	{
		words = xmalloc(100000 * sizeof(char *));
		i = 0;
		symbol = 0;
		ft_printf("token_type: %c ; token_content: %s\n", tokens->type, tokens->str);
		if (tokens->type == 's')
		{
			words[i++] = ft_strdup(tokens->str);
			words[i] = 0;
			symbol = 1;
		}
		else if (tokens->type == 'w')
		{
			while (tokens && tokens->type != 's')
			{
				words[i++] = ft_strdup(tokens->str);
				tokens = tokens->next;
			}
			words[i] = 0;
		}
		block_add_back(&blocks, block_new(words, symbol));
		if (tokens && symbol)
			tokens = tokens->next;
	}
	return (blocks);
}
