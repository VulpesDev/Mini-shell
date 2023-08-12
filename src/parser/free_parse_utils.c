/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:18:26 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/11 18:29:33 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"
#include <stdio.h>

void	free_condition(AstNode *ast);
void	free_pipeline(AstNode *ast);

void	free_command(AstNode *ast)
{
	token_free(ast->command_node.command);
	token_free(ast->command_node.redirections);
	free(ast);
}

void	free_pipeline(AstNode *ast)
{
	if (ast->type == AST_PIPELINE_NODE)
	{
		free_condition(ast->pipeline_node.left);
		free_condition(ast->pipeline_node.right);
		free(ast);
	}
	else
		free_command(ast);
}

void	free_condition(AstNode *ast)
{
	if (ast->type == AST_CONDITIONAL_NODE)
	{
		free_condition(ast->conditional_node.left);
		free_condition(ast->conditional_node.right);
		free(ast);
	}
	else
		free_pipeline(ast);
}

void	free_ast(AstNode *ast)
{
	free_condition(ast);
}