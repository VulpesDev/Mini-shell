/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:16:33 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/11 19:06:20 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include <stdio.h>

Token	*tokens;
Token	*parse_cache;
int		parse_status;

AstNode	*parser(char *line)
{
	Token	*tokens_freeme;
	AstNode	*ast;

	parse_status = 1;
	parse_cache = NULL;
	if (line == NULL)
		return (NULL);
	tokens = lexer(line);
	tokens_freeme = tokens;
	if (tokens == NULL)
		return NULL;
	ast = parse_expression();
	if (parse_status == 0 || tokens != NULL)
	{
		printf("Parsing FAILED!\n");
		free_ast(ast);
		token_free(tokens_freeme);
		return (NULL);
	}
	token_free(tokens_freeme);
	return (ast);
}