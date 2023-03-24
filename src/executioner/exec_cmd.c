/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:24:31 by tvasilev          #+#    #+#             */
/*   Updated: 2023/03/18 20:01:58 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:38:16 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/26 12:26:18 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "cmds.h"
#include "executioner.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

// ! return value of commands
// ! change exit status of exit
int	builtin_cmds(t_meta *meta)
{
	if (meta->cmd == NULL)
		return (0);
	if (!ft_strncmp("env", meta->cmd, 4))
		gs_env(meta->envp);
	else if (!ft_strncmp("exit", meta->cmd, 5))
		gs_exit(0);
	else if (!ft_strncmp("echo", meta->cmd, 5))
		gs_echo(&meta->cmd_args[1]);
	else if (!ft_strncmp("pwd", meta->cmd, 4))
		gs_pwd(&meta->cmd_args[1]);
	else if (!ft_strncmp("cd", meta->cmd, 3))
		gs_cd(&meta->cmd_args[1]);
	else if (!ft_strncmp("export", meta->cmd, 7))
		gs_export(&meta->cmd_args[1], meta);
	else if (!ft_strncmp("unset", meta->cmd, 7))
		gs_unset(&meta->cmd_args[1], meta);
	else
		return (0);
	return (1);
}

int	ext_cmds(t_meta *meta, t_vars *vars)
{
	if (*meta->cmd == '.')
	{
		vars->path_cmd = meta->cmd;
		if (!access(vars->path_cmd, F_OK))
		{
			execve(vars->path_cmd, meta->cmd_args, meta->envp);
			return (1);
		}
	}
	else
	{
		while (vars->paths[++vars->i])
		{
			vars->path_cmd = ft_strjoin(vars->paths[vars->i], meta->cmd);
			free(vars->paths[vars->i]);
			if (!access(vars->path_cmd, F_OK))
			{
				execve(vars->path_cmd, meta->cmd_args, meta->envp);
				free(vars->path_cmd);
				return (1);
			}
		}
	}
	return (0);
}

//? Add a return value to the executioner
int	exec_cmd(t_meta *meta)
{
	t_vars	vars;

	if (builtin_cmds(meta))
		return (1);
	vars.i = -1;
	vars.paths = get_paths(meta->envp);
	vars.child_pid = fork();
	vars.child_status = 1;
	if (vars.child_pid == 0)
	{
		if (!ext_cmds(meta, &vars))
			printf("command not found: %s\n", meta->cmd);
	}
	else
		waitpid(vars.child_pid, &vars.child_status, 0);
	free(vars.paths);
	//ft_printf("!!!return: %d\n", vars.child_status);
	return (vars.child_status);
}
