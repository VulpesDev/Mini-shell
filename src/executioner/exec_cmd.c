/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 15:24:31 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/26 21:52:42 by tvasilev         ###   ########.fr       */
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
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

// ! return value of commands
// ! change exit status of exit
int	builtin_cmds(char *cmd, char **cmd_args, char **envp)
{
	if (cmd == NULL)
		return (0);
	if (!ft_strncmp("env", cmd, 4))
		gs_env(envp);
	else if (!ft_strncmp("exit", cmd, 5))
		gs_exit(0);
	else if (!ft_strncmp("echo", cmd, 5))
		gs_echo(cmd_args);
	else if (!ft_strncmp("pwd", cmd, 4))
		gs_pwd(cmd_args);
	else if (!ft_strncmp("cd", cmd, 3))
		gs_cd(cmd_args);
	else if (!ft_strncmp("export", cmd, 7))
		gs_export(cmd_args, envp);
	else if (!ft_strncmp("unset", cmd, 7))
		gs_unset(cmd_args, envp);
	else
		return (0);
	return (1);
}

void	ext_cmds(char *cmd, char **cmd_args, char **envp, t_vars *vars)
{
	if (*cmd == '.')
	{
		vars->path_cmd = cmd;
		if (!access(vars->path_cmd, F_OK))
			execve(vars->path_cmd, cmd_args, envp);
	}
	else
	{
		while (vars->paths[++vars->i])
		{
			vars->path_cmd = ft_strjoin(vars->paths[vars->i], cmd);
			free(vars->paths[vars->i]);
			if (!access(vars->path_cmd, F_OK))
			{
				execve(vars->path_cmd, cmd_args, envp);
				free(vars->path_cmd);
				break ;
			}
		}
	}
}

//? Add a return value to the executioner
int	exec_cmd(char *cmd, char **cmd_args, char **envp)
{
	t_vars	vars;

	if (builtin_cmds(cmd, cmd_args, envp))
		return (1);
	vars.i = -1;
	vars.paths = get_paths(envp);
	vars.child_pid = fork();
	vars.child_status = 1;
	if (vars.child_pid == 0)
		ext_cmds(cmd, cmd_args, envp, &vars);
	else
		waitpid(vars.child_pid, &vars.child_status, 0);
	free(vars.paths);
	ft_printf("!!!return: %d\n", vars.child_status);
	return (vars.child_status);
}
