/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:43:22 by tvasilev          #+#    #+#             */
/*   Updated: 2023/03/28 12:47:25 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<unistd.h>
#include "libft.h"
#include "cmds.h"
#include "utils.h"
#define PWD_SIZE 10000

int	gs_cd_protect(char	*path)
{
	if (chdir(path))
	{
		ft_fprintf(2, "cd: no such file or directory: %s\n", path);
		return (1);
	}
	return (0);
}

int	gs_cd(char	**cmd_args)
{
	if (cmd_args[1])
	{
		ft_fprintf(2, "cd: too many arguments\n");
		return (1);
	}
	else if (!cmd_args[0])
		return (gs_cd_protect(getenv("HOME")));
	else if (!ft_strncmp("~", cmd_args[0], 2))
		return (gs_cd_protect(getenv("HOME")));
	else
		return (gs_cd_protect(cmd_args[0]));
}

void	gs_echo_print(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && strs[i + 1])
	{
		ft_printf("%s ", strs[i]);
		i++;
	}
	ft_printf("%s", strs[i]);
}

int	gs_echo(char **cmd_args)
{
	if (!*cmd_args)
		ft_printf("\n");
	else if (!ft_strncmp(cmd_args[0], "-n", 3))
		gs_echo_print(&cmd_args[1]);
	else
	{
		gs_echo_print(&cmd_args[0]);
		ft_printf("\n");
	}
	return (0);
}

int	gs_env(char **envp)
{
	if (envp == NULL)
		return (1);
	print_strs(envp);
	return (0);
}

void	gs_exit(int status)
{
	exit(status);
}

//? Validate input
//? when more than one equal sign, problems
//? when old_split fails maybe I have to free new_split ?
int	gs_validate_export(char **cmd_args)
{
	int	i;
	int	j;

	i = -1;
	if (!cmd_args)
		return (1);
	while (cmd_args[++i])
	{
		j = -1;
		if (!cmd_args[i])
			return (1);
		while (cmd_args[i][++j])
			if (!ft_isalnum(cmd_args[i][j]) && cmd_args[i][j] != '=')
				return (1);
	}
	return (0);
}

//Allocates a new envp and adds a new variable 
void	gs_create_export(char **cmd_args, t_meta *meta, int i)
{
	char	**new_env;
	int		len;
	int		k;

	k = -1;
	len = dp_size((meta->envp));
	new_env = xmalloc(len * sizeof(char *) + 2);
	while (++k < len)
		new_env[k] = ft_strdup(meta->envp[k]);
	new_env[k++] = ft_strdup(cmd_args[i]);
	new_env[k] = NULL;
	free(meta->envp);
	meta->envp = new_env;
}

//Edits export dp Returns found(bool)
int	gs_edit_export(char **cmd_args, t_meta *meta, char **new_split, int i)
{
	char	**old_split;
	int		j;

	j = -1;
	while (meta->envp[++j])
	{
		old_split = ft_split(meta->envp[j], '=');
		malloc_check(old_split);
		if (!ft_strncmp(old_split[0], new_split[0],
				ft_strlen(old_split[0]) + ft_strlen(new_split[0])))
		{
			free(meta->envp[j]);
			meta->envp[j] = ft_strdup(cmd_args[i]);
			malloc_check(meta->envp[j]);
			return (1);
		}
		dp_free(old_split);
	}
	return (0);
}

int	gs_export(char **cmd_args, t_meta *meta)
{
	int		i;
	char	**new_split;
	int		found;

	i = -1;
	if (!cmd_args[0])
		gs_env(meta->envp);
	if (gs_validate_export(cmd_args))
	{
		ft_fprintf(2, "ERROR!\n");
		return (1);
	}
	while (cmd_args[++i])
	{
		found = 0;
		new_split = ft_split(cmd_args[i], '=');
		malloc_check(new_split);
		if (!gs_edit_export(cmd_args, meta, new_split, i))
			gs_create_export(cmd_args, meta, i);
		dp_free(new_split);
	}
	return (0);
}

int	gs_pwd_error(const char *message)
{
	ft_fprintf(2, "pwd: %s\n", message);
	return (1);
}

int	gs_pwd(char **cmd_args)
{
	char	*buf;

	if (*cmd_args)
		return gs_pwd_error("too many arguments");
	buf = xmalloc(PWD_SIZE * sizeof(char));
	getcwd(buf, PWD_SIZE);
	ft_printf("%s\n", buf);
	return (0);
}

int	gs_validate_unset(char **cmd_args)
{
	int	i;
	int	j;

	i = -1;
	if (!cmd_args)
		return (1);
	while (cmd_args[++i])
	{
		j = -1;
		if (!cmd_args[i])
			return (1);
		while (cmd_args[i][++j])
			if (!ft_isalnum(cmd_args[i][j]) && cmd_args[i][j] != '=')
				return (1);
	}
	return (0);
}

int	gs_remove_unset(t_meta *meta, char *str)
{
	char	**old_split;
	int		j;

	j = -1;
	while (meta->envp[++j])
	{
		old_split = ft_split(meta->envp[j], '=');
		malloc_check(old_split);
		if (!ft_strncmp(old_split[0], str,
				ft_strlen(old_split[0]) + ft_strlen(str)))
		{
			free(meta->envp[j]);
			while (meta->envp[j + 1])
			{
				meta->envp[j] = meta->envp[j + 1];
				j++;
			}
			meta->envp[j] = NULL;
		}
		dp_free(old_split);
	}
	return (0);
}

int	error(char **cmd_args)
{
	if (!cmd_args[0])
	{
		ft_fprintf(2, "unset: not enough arguments\n");
		return (1);
	}
	if (gs_validate_unset(cmd_args))
	{
		ft_fprintf(2, "ERROR!\n");
		return (1);
	}
	return (0);
}

int	gs_unset(char **cmd_args, t_meta *meta)
{
	int		i;

	if (!cmd_args[0] || !gs_validate_unset(cmd_args))
		return (error(cmd_args));
	i = -1;
	while (cmd_args[++i])
		return (gs_remove_unset(meta, cmd_args[i]));
	return (0);
}
