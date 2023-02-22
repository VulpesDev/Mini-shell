/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:42:06 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/22 12:43:14 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/*split the tokens into code blocks separetaed by
the symbols*/
t_code_block	*parser(t_meta *meta, t_token *tokens);

void			block_clear(t_code_block **lst);

t_code_block	*block_new(char **words, int symbol);

t_code_block	*block_last(t_code_block *lst);

void			block_add_back(t_code_block **lst, t_code_block *new_elem);

#endif