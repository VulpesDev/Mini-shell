/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:38:16 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/26 19:32:52 by lmiehler         ###   ########.fr       */
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

void	check_commands(t_meta *meta)
{
	if (meta->cmd == NULL)
		return ;
	if (!ft_strncmp("env", meta->cmd, 4))
		gs_env(meta->envp);
	else if (!ft_strncmp("exit", meta->cmd, 5))
		gs_exit(meta->exit_status);
	else if (!ft_strncmp("echo", meta->cmd, 5))
		gs_echo(meta->cmd_args);
	else if (!ft_strncmp("pwd", meta->cmd, 4))
		gs_pwd(meta);
	else if (!ft_strncmp("cd", meta->cmd, 3))
		gs_cd(meta);
	else if (!ft_strncmp("export", meta->cmd, 7))
		gs_export(meta->cmd_args, meta);
	else if (!ft_strncmp("unset", meta->cmd, 7))
		gs_unset(meta->cmd_args, meta);
}

int	redirect(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		printf("dup2 failed\n");
		return (0);
	}
	return (1);
}

int	executioner(t_meta *meta)
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