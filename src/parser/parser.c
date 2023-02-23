/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:38:06 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/23 18:24:41 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "cmds.h"
#include "utils.h"
#include "expander.h"

void parser(t_meta *meta, const char *str)
{
	char **strs;

	//!Just pressing enter creates segv
	//!MUST FREE strs on exit
	// Temporary fix for if str == NULL
	if (!str)
		strs = NULL;
	else
	{
		char **tmp;
		strs = ft_split(str, ' '); //! if split == NULL - segv
		meta->cmd = strs[0];
		meta->cmd_args = &strs[1];
		//ft_printf("Wildcards\n");
		//print_strs(expand_wildcards(meta->cmd_args[0]));
		tmp = expander(meta->cmd_args[0], meta->envp);
		ft_printf("====EXPANDED====\n");
		print_strs(tmp);
		ft_printf("====EXPAND FIN====\n");
		meta->cmd_args[0] = tmp[0];
		//meta->cmd_args[0] = remove_quotes(meta->cmd_args[0]);
	}
}
