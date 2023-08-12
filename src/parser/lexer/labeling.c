/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labeling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:50:57 by tvasilev          #+#    #+#             */
/*   Updated: 2023/04/26 15:08:34 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	assign_token_type(Token *tokens)
{
	if (!ft_strncmp(tokens->word, "||", 2))
		tokens->type = TOK_OR;
	else if (!ft_strncmp(tokens->word, "&&", 2))
		tokens->type = TOK_AND;
	else if (!ft_strncmp(tokens->word, ">>", 2))
		tokens->type = TOK_REDIRECT_APPEND;
	else if (!ft_strncmp(tokens->word, "<<", 2))
		tokens->type = TOK_REDIRECT_HEREDOC;
	else if (!ft_strncmp(tokens->word, "|", 1))
		tokens->type = TOK_PIPE;
	else if (!ft_strncmp(tokens->word, "(", 1))
		tokens->type = TOK_LPAREN;
	else if (!ft_strncmp(tokens->word, ")", 1))
		tokens->type = TOK_RPAREN;
	else if (!ft_strncmp(tokens->word, ">", 1))
		tokens->type = TOK_REDIRECT_OUT;
	else if (!ft_strncmp(tokens->word, "<", 1))
		tokens->type = TOK_REDIRECT_IN;
	else
		tokens->type = TOK_WORD;
}

Token	*labeling(Token *tokens)
{
	Token	*result;

	result = tokens;
	while (tokens)
	{
		assign_token_type(tokens);
		tokens = tokens->next;
	}
	return (result);
}
