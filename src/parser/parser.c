/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:38:06 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/14 12:03:41 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "cmds.h"
#include "utils.h"

void parser(t_meta *meta, const char *str)
{
	char **strs;

	// Bullshit
	//!Just pressing enter creates segv
	strs = ft_split(str, ' '); //! if split == NULL - segv
	meta->cmd = strs[0];
	meta->cmd_args = &strs[1];
}
