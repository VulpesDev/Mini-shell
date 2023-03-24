/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
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
	
}