/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:25:53 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/24 17:11:51 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "builtins.h"
#include "interpreter.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "parser.h"

extern PidList	*g_pid_list;

void	cleanup(void)
{
	pidList_clear(&g_pid_list);
	dp_free(g_envp);
}
