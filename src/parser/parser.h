/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:42:06 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/22 12:01:00 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

t_code_block	*parser(t_meta *meta, t_token *tokens);

void			block_clear(t_code_block **lst);

t_code_block	*block_new(char **words, int symbol);

t_code_block	*block_last(t_code_block *lst);

void			block_add_back(t_code_block **lst, t_code_block *new_elem);

#endif