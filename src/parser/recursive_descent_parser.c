/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_descent_parser.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:39:28 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/24 17:07:37 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include <stdio.h>

/*
	Extended-Backus-Naur-Form (EBNF):

	<expression> ::= <pipeline> {('&&' | '||') <pipeline>}
	<pipeline> ::= <command> {'|' <command>}
	<command> ::= (<word> | <redirection>) {<word> | <redirection>}
	<command> ::= '(' <expression> ')'
	<redirection> ::= ('>' | '>>' | '<' | '<<') <word>
	<word> ::= <ascii_char> {<ascii_char>}
*/

//------Recursive Descent Parser------

AstNode	*parse_command( void )
{
	Token	*redirections;
	Token	*command;
	AstNode	*node;

	node = NULL;
	if (accept(TOK_LPAREN))
	{
		node = parse_expression();
		expect(TOK_RPAREN);
	}
	else
	{
		command = NULL;
		redirections = NULL;
		if (accept_redirection())
		{
			token_add_back(&redirections, token_copy(parse_cache));
			if (expect(TOK_WORD))
				token_add_back(&redirections, token_copy(parse_cache));
		}
		else if (expect(TOK_WORD))
		{
			token_add_back(&command, token_copy(parse_cache));
		}
		while (true)
		{
			if (accept_redirection())
			{
				token_add_back(&redirections, token_copy(parse_cache));
				if (expect(TOK_WORD))
					token_add_back(&redirections, token_copy(parse_cache));
			}
			else if (accept(TOK_WORD))
			{
				token_add_back(&command, token_copy(parse_cache));
			}
			else
				break ;
		}
		node = build_command(command, redirections);
	}
	return (node);
}

AstNode	*parse_pipeline( void )
{
	AstNode	*node;

	node = parse_command();
	while (accept(TOK_PIPE))
	{
		node = build_pipeline(node, parse_command());
	}
	return (node);
}

AstNode	*parse_expression( void )
{
	AstNode	*node;

	node = parse_pipeline();
	while (true)
	{
		if (accept(TOK_AND))
			node = build_condition(node, parse_pipeline(), COND_AND);
		else if (accept(TOK_OR))
			node = build_condition(node, parse_pipeline(), COND_OR);
		else
			break ;
	}
	return (node);
}
