/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:38:16 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/25 18:47:15 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "cmds.h"
#include "executioner.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

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

//? Add a return value to the executioner
int	executioner(t_meta *meta)
{
	int		i;
	int		child_pid;
	int		child_status;
	char	*path_cmd;
	char	**paths;

	i = -1;
	paths = get_paths(meta);
	child_pid = fork();
	child_status = 1;
	if (child_pid == 0)
	{ 
		if (*meta->cmd == '.')
		{
			path_cmd = meta->cmd;
			if (!access(path_cmd, F_OK))
				execve(path_cmd, meta->cmd_args, meta->envp);
		}
		else
		{
			while (paths[++i])
			{
				path_cmd = ft_strjoin(paths[i], meta->cmd);
				free(paths[i]);
				if (!access(path_cmd, F_OK))
				{
					execve(path_cmd, meta->cmd_args, meta->envp);
					free(path_cmd);
					break ;
				}
			}
		}
	}
	else
		waitpid(child_pid, &child_status, 0);
	free(paths);
	ft_printf("!!!return: %d\n", child_status);
	return (child_status);
}