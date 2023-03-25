/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:24:31 by tvasilev          #+#    #+#             */
/*   Updated: 2023/03/25 03:19:03 by tvasilev         ###   ########.fr       */
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
#define CMD_FOUND_NOT 127

// ! return value of commands
// ! change exit status of exit
int	builtin_cmds(t_meta *meta, t_vars *vars)
{
	if (meta->cmd == NULL)
		return (1);
	if (!ft_strncmp("env", meta->cmd, 4))
		return (gs_env(meta->envp));
	else if (!ft_strncmp("exit", meta->cmd, 5))
		return (gs_exit(0));
	else if (!ft_strncmp("echo", meta->cmd, 5))
		return (gs_echo(&meta->cmd_args[1]));
	else if (!ft_strncmp("pwd", meta->cmd, 4))
		return (gs_pwd(&meta->cmd_args[1]));
	else if (!ft_strncmp("cd", meta->cmd, 3))
		return (gs_cd(&meta->cmd_args[1]));
	else if (!ft_strncmp("export", meta->cmd, 7))
		return (gs_export(&meta->cmd_args[1], meta));
	else if (!ft_strncmp("unset", meta->cmd, 7))
		return (gs_unset(&meta->cmd_args[1], meta));
	return (127);
}

int	ext_cmds(t_meta *meta, t_vars *vars)
{
	if (*meta->cmd == '.')
	{
		vars->path_cmd = meta->cmd;
		if (!access(vars->path_cmd, F_OK))
		{
			execve(vars->path_cmd, meta->cmd_args, meta->envp);
			return (0);
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
				return (0);
			}
		}
	}
	return (1);
}

int cmd_not_found(t_meta *meta)
{
	printf("command not found: %s\n", meta->cmd);
	return (CMD_FOUND_NOT);
}

//? Add a return value to the executioner
int	exec_cmd(t_meta *meta)
{
	t_vars	vars;

	vars.paths = get_paths(meta->envp);
	vars.child_status = 1;
	vars.child_status = builtin_cmds(meta, &vars);
	if (!vars.child_status)
	{
		ft_printf("!!!return: %d\n", vars.child_status);
		return (vars.child_status);
	}
	if (vars.child_status != 127)
		return (vars.child_status);
	vars.i = -1;
	vars.child_pid = fork();
	if (vars.child_pid == 0)
	{
		if (ext_cmds(meta, &vars))
			return (cmd_not_found(meta));
	}
	else
		waitpid(vars.child_pid, &vars.child_status, 0);
	free(vars.paths);
	ft_printf("!!!return: %d\n", vars.child_status);
	return (vars.child_status);
}