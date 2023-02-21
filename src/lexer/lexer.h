/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:31:27 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/21 11:09:20 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# include "libft.h"
# include "utils.h"
# include <stdlib.h>

t_token	*lexer(char *str);

char	**lexical_split(char *s);

void	split_spaces(char *s, char **result);

char	**symbolical_split(char *s, char *c);

t_token	*token_new(char *str, char type);

t_token	*token_last(t_token *lst);

void	token_clear(t_token **lst);

void	token_add_back(t_token **lst, t_token *new_elem);

#endif