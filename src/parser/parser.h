/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:15:30 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/09 13:16:14 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>
# include <stdlib.h>
# include "minishell.h"

// Parser data
extern Token *tokens;
extern Token *parse_cache;
extern int parse_status;

// Call to parser
AstNode	*parser(char *line);

// Utils
void	print_ast(AstNode *ast);
void	free_ast(AstNode *ast);

// Node building
AstNode	*build_command(Token *command, Token *redirections);
AstNode	*build_pipeline(AstNode *left, AstNode *right);
AstNode	*build_condition(AstNode *left, AstNode *right, ConditionalType type);

// Recursive-Descent-Parser entry point
AstNode	*parse_expression( void );

// Token stream manipulation
int		accept(TokenType type);
int		expect(TokenType type);
int		accept_redirection( void );



# define TOK_REDIRECTION 99

#endif