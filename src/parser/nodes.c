/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:20:33 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/21 15:27:00 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

AstNode	*build_command(Token *command, Token *redirections)
{
	AstNode	*node;

	node = xmalloc(sizeof(AstNode));
	node->type = AST_COMMAND_NODE;
	node->command_node.command = command;
	node->command_node.redirections = redirections;
	return (node);
}

AstNode	*build_pipeline(AstNode *left, AstNode *right)
{
	AstNode	*node;

	node = xmalloc(sizeof(AstNode));
	node->type = AST_PIPELINE_NODE;
	node->pipeline_node.left = left;
	node->pipeline_node.right = right;
	return (node);
}

AstNode	*build_condition(AstNode *left, AstNode *right, ConditionalType type)
{
	AstNode	*node;

	node = xmalloc(sizeof(AstNode));
	node->type = AST_CONDITIONAL_NODE;
	node->conditional_node.type = type;
	node->conditional_node.left = left;
	node->conditional_node.right = right;
	return (node);
}