/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:17:55 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/11 18:25:09 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include <stdio.h>

//------Token stream manipulation------

int	accept_redirection( void )
{
	if (accept(TOK_REDIRECT_IN)
		|| accept(TOK_REDIRECT_OUT)
		|| accept(TOK_REDIRECT_APPEND)
		|| accept(TOK_REDIRECT_HEREDOC))
		return (true);
	return (false);
}

int	accept(TokenType type)
{
	if (tokens == NULL || parse_status == 0)
		return (false);
	if (tokens->type == type)
	{
		parse_cache = tokens;
		tokens = tokens->next;
		return (true);
	}
	return (false);
}

int	expect(TokenType type)
{
	if (parse_status == 0)
		return (false);
	if (accept(type))
		return (true);
	parse_status = 0;
	return (false);
}

//------Print AST------

// void _expression(AstNode *ast);

// void print_ast_command(AstNode *ast)
// {
// 	Token *cur_cmd = ast->command_node.command;
// 	Token *cur_redirs = ast->command_node.redirections;;
// 	if (ast->type == AST_COMMAND_NODE) {
// 		while (cur_cmd) {
// 			if (cur_cmd->next == NULL
// 				&& cur_redirs == NULL)
// 				printf("%s", cur_cmd->word);
// 			else
// 				printf("%s ", cur_cmd->word);
// 			cur_cmd = cur_cmd->next;
// 		}
// 		while (cur_redirs) {
// 			if (cur_redirs->type == TOK_REDIRECT_IN)
// 				printf("<");
// 			else if (cur_redirs->type == TOK_REDIRECT_OUT)
// 				printf(">");
// 			else if (cur_redirs->type == TOK_REDIRECT_APPEND)
// 				printf(">>");
// 			else if (cur_redirs->type == TOK_REDIRECT_HEREDOC)
// 				printf("<<");
// 			cur_redirs = cur_redirs->next;
// 			if (cur_redirs->next == NULL)
// 				printf("%s", cur_redirs->word);
// 			else
// 				printf("%s ", cur_redirs->word);
// 			cur_redirs = cur_redirs->next;
// 		}
// 	}
// 	else {
// 		//printf("[E](");
// 		print_ast_expression(ast);
// 		//printf(")");
// 	}
// }

// void print_ast_pipeline(AstNode *ast)
// {
// 	if (ast->type == AST_PIPELINE_NODE) {
// 		printf("P(");
// 		print_ast_command(ast->pipeline_node.left);
// 		printf(" | ");
// 		print_ast_command(ast->pipeline_node.right);
// 		printf(")");
// 	}
// 	else
// 		print_ast_command(ast);
// }

// void print_ast_expression(AstNode *ast)
// {
// 	if (ast->type == AST_CONDITIONAL_NODE) {
// 		printf("C(");
// 		print_ast_pipeline(ast->conditional_node.left);
// 		if (ast->conditional_node.type == COND_AND)
// 			printf(" && ");
// 		else
// 			printf(" || ");
// 		print_ast_pipeline(ast->conditional_node.right);
// 		printf(")");
// 	}
// 	else
// 		print_ast_pipeline(ast);
// }

// void print_ast(AstNode *ast)
// {
// 	printf("AST generated: ");
// 	if (ast == NULL) {
// 		printf("Empty\n");
// 		return;
// 	}
// 	print_ast_expression(ast);
// 	printf("\n");
// }

//------Free AST------
