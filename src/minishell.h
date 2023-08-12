/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:20:27 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/21 15:28:23 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT_ISLAND "\033[0;32m<Island>~\033[0m "
# define PROMPT_ATLANTIS "\033[0;34m~Atlantis~\033[0m "
# define PROMPT_MINIHELL "\033[0;31mMinihell:\033[0m "

//#define fprintf(...)

#include <stdlib.h>

extern char **g_envp;

//------Token Data Structure for the Lexer------

typedef enum TokenType	TokenType;

typedef struct Token
{
	enum	TokenType
	{
		TOK_NONE,
		TOK_WORD,
		TOK_PIPE,
		TOK_REDIRECT_IN,
		TOK_REDIRECT_OUT,
		TOK_REDIRECT_APPEND,
		TOK_REDIRECT_HEREDOC,
		TOK_AND,	
		TOK_OR,
		TOK_LPAREN,
		TOK_RPAREN
	}				type;
	char			*word;
	struct Token	*next;
}Token;

//------Abstract Syntax Tree Data Structure for the Parser------

typedef enum ConditionalType ConditionalType;

typedef struct CommandNode
{
	Token	*command;
	Token	*redirections;
}CommandNode;

typedef struct PipelineNode
{
	struct AstNode	*left;
	struct AstNode	*right;
}PipelineNode;

typedef struct ConditionalNode
{
	enum	ConditionalType
	{
		COND_AND,
		COND_OR
	}				type;
	struct AstNode	*left;
	struct AstNode	*right;
}ConditionalNode;

typedef struct AstNode
{
	enum	AstNodeType
	{
		AST_COMMAND_NODE,
		AST_PIPELINE_NODE,
		AST_CONDITIONAL_NODE
	}type;
	union
	{
		struct CommandNode		command_node;
		struct PipelineNode		pipeline_node;
		struct ConditionalNode	conditional_node;
	};
}		AstNode;

// Core functions
void	setup(char **envp);
void	cleanup( void );
void	*xmalloc(size_t size);

#endif