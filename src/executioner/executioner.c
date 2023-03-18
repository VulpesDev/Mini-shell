/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:38:16 by lmiehler          #+#    #+#             */
/*   Updated: 2023/03/18 12:16:56 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include<unistd.h>
#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "executioner.h"
//? Add a return value to the executioner
int	executioner(t_code_block *blocks, t_meta *meta)
{
	int stdin = dup(0);
	int stdout = dup(1);
	int fd[2];
	pipe(fd);
	t_code_block *cur;
	cur = blocks;
	while (cur)
	{
		if (!cur->symbol)
		{
			meta->cmd = cur->words[0];
			meta->cmd_args = cur->words;
			exec_cmd(meta);
		}
		cur = cur->next;
	}
	return (0);
}