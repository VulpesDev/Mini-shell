/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:31:27 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/27 13:27:55 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# include "libft.h"
# include "utils.h"
# include <stdlib.h>
# define SYMBOL_ERROR "parse error\n"

t_token	*lexer(char *str, char **envp);

/*first part of the lexer, splits the str
taking spaces/tabs...etc. as a delimiter
it also considers q(quotes) and dq*/
char	**lexical_split(char *s);

/*main helper for lexical split*/
void	split_spaces(char *s, char **result);

/*the second part of the lexer, splts the str
taking all the symbols
(< > << >> | || & &&) as a delimiter and
also considers q and dq*/
char	**symbolical_split(char *s, char *c);

/*main helper for symbolical split*/
void	split_symbol(char *s, char *c, char **result);

/*creates and allocates space for new token*/
t_token	*token_new(char *str, char type);

/*gets the last token in the list*/
t_token	*token_last(t_token *lst);

/*clears a token list*/
void	token_clear(t_token **lst);

/*adds a token to the back of a token list*/
void	token_add_back(t_token **lst, t_token *new_elem);

int		validate(t_token *blocks);

int		print_error(void);

#endif