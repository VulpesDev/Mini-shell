/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:38:16 by lmiehler          #+#    #+#             */
/*   Updated: 2023/03/24 18:39:46 by tvasilev         ###   ########.fr       */
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
	t_code_block *cur, *next, *prev = 0;
	cur = blocks;
	while (cur)
	{
		if (!cur->symbol)
		{
			next = cur->next;
			if (next && next->symbol && !ft_strncmp(next->words, "||", 2))
			{
				dup2(fd[1], 1);
				meta->cmd = cur->words[0];
				meta->cmd_args = cur->words;
				exec_cmd(meta);
				if (prev && prev->symbol)
				{
					dup2(fd[0], 0);
					meta->cmd = cur->words[0];
					meta->cmd_args = cur->words;
					dup2(stdout, 1);
					exec_cmd(meta);
					dup2(stdin, 0);
				}
			}
		}
		prev = cur;
		cur = cur->next;
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}