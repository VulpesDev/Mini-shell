/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:55:47 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/02 13:54:05 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "../../minishell.h"
# include "../../../libft/src/libft.h"
# include <stdlib.h>

char	*ft_strncpy(char *src, int len);

Token	*token_create(void *content);

Token	*token_last(Token *lst);

Token	*token_copy(Token *tok);

void	token_add_back(Token **lst, Token *new_elem);

void	token_print(Token *tok);

Token	*split_by_whitespace(Token single);

Token	*split_by_symbols(Token single);

Token	*labeling(Token *tokens);

Token	*lexer(char *line);

void	init_vars(char **set, int splitter[], int quot[], Token **r);

void	check_quot(int quot[], char c);

void	add_cur_token(Token **result, Token *single, int splitter[]);

void	increment(int splitter[]);

void	*xmalloc(size_t size);

char	*ft_strdup(const char *s);

Token	*token_copy(Token *tok);

void	token_free(Token *tok);

#endif