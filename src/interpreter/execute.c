/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:43:20 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/24 17:27:28 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include "interpreter.h"
#include "lexer.h"
#include "expander.h"
#include "parser.h"
#include "interpreter.h"
#include "builtins.h"

extern PidList	*g_pid_list;
AstNode *g_ast;

void	free_strs(char *strs[])
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	*get_path(char *envp[])
{
	while (*envp)
	{
		if (!ft_strncmp("PATH=/", *envp, 6))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*get_cmd_path(char *path, char *cmd)
{
	int		i;
	char	**paths;
	char	*cur_path;
	char	*cmd_path;

	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		cur_path = ft_strjoin(paths[i], "/");
		cmd_path = ft_strjoin(cur_path, cmd);
		free(cur_path);
		if (!access(cmd_path, F_OK | X_OK))
		{
			free_strs(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_strs(paths);
	return (NULL);
}

int list_length(Token *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

char	**list_to_arr(Token *lst)
{
	char	**strs;
	int		i;

	i = 0;
	strs = xmalloc(sizeof(char *) * (list_length(lst) + 1));
	while (lst)
	{
		strs[i] = strdup(lst->word);
		i++;
		lst = lst->next;
	}
	strs[i] = NULL;
	return (strs);
}

void	cleanup_processes(PidList *cur)
{
	while (cur)
	{
		kill(cur->pid, SIGINT);
		cur = cur->next;
	}
}

int	builtin_cmds(char *cmd, char **args, char **cmds)
{
	if (cmd == NULL)
		return (1);
	if (!ft_strncmp("env", cmd, 4))
		return (gs_env());
	else if (!ft_strncmp("exit", cmd, 5))
	{
		while (pipe_stack) {
			stack_pop(&pipe_stack);
		}
		int atoi = args[0] ? ft_atoi(args[0]) : 0;
		dp_free(cmds);
		free_ast(g_ast);
		gs_exit(atoi);
	}
	else if (!ft_strncmp("echo", cmd, 5))
		return (gs_echo(args));
	else if (!ft_strncmp("pwd", cmd, 4))
		return (gs_pwd(args));
	else if (!ft_strncmp("cd", cmd, 3))
		return (gs_cd(args));
	else if (!ft_strncmp("export", cmd, 7))
		return (gs_export(args));
	else if (!ft_strncmp("unset", cmd, 7))
		return (gs_unset(args));
	return (127);
}

int last_proc(int is_last, int pid, int *status)
{
	if (is_last)
	{
		waitpid(pid, status, 0);
		cleanup_processes(g_pid_list);
		recent_exit_status = WEXITSTATUS(*status);
		return (!WEXITSTATUS(*status));
	}
	return (1);
}

int do_path(char *cmd_path, char **cmds)
{
	char *get_path_occ_c = get_path(g_envp);
	if (get_path_occ_c == NULL)
	{
		fprintf(stderr, "[Error]: Command not found %s\n", cmds[0]);
		return (0);
	}
	cmd_path = get_cmd_path(get_path_occ_c, cmds[0]);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "[Error]: Command not found %s\n", cmds[0]);
		cleanup_processes(g_pid_list);
		return (0);
	}
	free(cmds[0]);
	cmds[0] = cmd_path;
	return (1);
}

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int	execute_command(Token *command, bool is_last)
{
	int		status, pid;
	char	**cmds;
	char	*cmd_path;

	status = 0;
	cmd_path = NULL;
	if (command == NULL)
		return (1);
	command = expander(command);
	cmds = list_to_arr(command);
	token_free(command);
	status = builtin_cmds(cmds[0], &cmds[1], cmds);
	if (is_last && status != 127)
		recent_exit_status = status;
	if (status != 127)
	{
		dp_free(cmds);
		return (!status);
	}
	if (access(cmds[0], F_OK | X_OK))
	{
		if (!do_path(cmd_path, cmds))
		{
			dp_free(cmds);
			recent_exit_status = 127;
			return (0);
		}
	}
	if (!is_regular_file(cmds[0])) {
		fprintf(stderr, "[Error]: Command not found %s\n", cmds[0]);
		recent_exit_status = 127;
		dp_free(cmds);
		return (0);
	}
	pid = fork();
	if (!is_last)
		pidList_add(&g_pid_list, pidList_create(pid));
	if (pid == 0)
	{
		int is_first = 1;
		Stack *cur = pipe_stack;
		while (cur) {
			if (is_first) {
				is_first = 0;
				if (cur->written_to == 0)
					close(cur->pd[0]);
				else
					close(cur->pd[1]);
			}
			else {
				close(cur->pd[1]);
				close(cur->pd[0]);
			}
			cur = cur->next;
		}
		execve(cmds[0], cmds, g_envp);
		exit(1);
	}
	dp_free(cmds);
	return (last_proc(is_last, pid, &status));
}