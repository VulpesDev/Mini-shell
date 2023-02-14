/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:38:06 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/14 11:22:48 by tvasilev         ###   ########.fr       */
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
	strs = ft_split(str, ' '); //! if split == NULL - segf
	meta->cmd = strs[0];
	meta->cmd_args = &strs[1];
}