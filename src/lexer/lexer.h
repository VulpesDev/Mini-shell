/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:31:27 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/17 12:08:23 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "minishell.h"
# include "libft.h"
# include "utils.h"
# include <stdlib.h>

void	lexer(char *str);

char	**lexical_split(char *s, char c);

char	**symbolical_split(char *s, char *c);

#endif