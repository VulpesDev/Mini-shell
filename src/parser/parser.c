/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:38:06 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/22 16:55:55 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "parser.h"
#include <stdlib.h>

static int	handle_files(t_meta *meta, t_token **tokens)
{
	if (!ft_strncmp((*tokens)->str, ">>", 2)
		|| !ft_strncmp((*tokens)->str, ">", 2))
	{
		(*tokens) = (*tokens)->next;
		meta->outfile.file = ft_strdup((*tokens)->str);
		if (!ft_strncmp((*tokens)->str, ">>", 2))
			meta->infile.append = 1;
		else
			meta->infile.append = 0;
	}
	else if (!ft_strncmp((*tokens)->str, "<<", 2)
		|| !ft_strncmp((*tokens)->str, "<", 2))
	{
		(*tokens) = (*tokens)->next;
		meta->infile.file = ft_strdup((*tokens)->str);
		if (!ft_strncmp((*tokens)->str, "<<", 2))
			meta->infile.append = 1;
		else
			meta->infile.append = 0;
	}
	else
		return (0);
	return (1);
}

static void	handle_symb(t_meta *meta, t_token **tokens, char **words, int bool_s[])
{
	int	i;

	i = 0;
	if (handle_files(meta, tokens))
	{
		if (*tokens)
			*tokens = (*tokens)->next;
		free(words);
		bool_s[1] = 1;
	}
	else
	{
		words[i++] = ft_strdup((*tokens)->str);
		words[i] = 0;
		bool_s[0] = 1;
	}
}

static void	handle_words(t_token **tokens, char **words)
{
	int	i;

	i = 0;
	while ((*tokens) && (*tokens)->type != 's')
	{
		words[i++] = ft_strdup((*tokens)->str);
		(*tokens) = (*tokens)->next;
	}
	words[i] = 0;
}

t_code_block	*parser(t_meta *meta, t_token *tokens)
{
	t_code_block	*blocks;
	char			**words;
	int				bool_s[2];

	blocks = 0;
	while (tokens)
	{
		bool_s[1] = 0;
		words = xmalloc(100000 * sizeof(char *));
		bool_s[0] = 0;
		if (tokens->type == 's')
			handle_symb(meta, &tokens, words, bool_s);
		else if (tokens->type == 'w')
			handle_words(&tokens, words);
		if (!bool_s[1])
			block_add_back(&blocks, block_new(words, bool_s[0]));
		if (tokens && bool_s[0])
			tokens = tokens->next;
	}
	return (blocks);
}
