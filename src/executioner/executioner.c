/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:38:16 by lmiehler          #+#    #+#             */
/*   Updated: 2023/03/25 03:19:03 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "cmds.h"
#include "executioner.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int	redirect(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		printf("dup2 failed\n");
		return (0);
	}
	return (1);
}

int	executioner(t_code_block *blocks, t_meta *meta)
{
	t_code_block *cur;
	cur = blocks;
	while (cur)
	{
		meta->cmd = cur->words[0];
		meta->cmd_args = cur->words;
		exec_cmd(meta);
		cur = cur->next;
	}
	return (0);
}