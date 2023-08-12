/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:26:49 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/24 18:05:26 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	gs_validate_export(char **cmd_args)
{
	int	i;
	int	j;
	int status;

	i = -1;
	if (!cmd_args)
		return (1);
	while (cmd_args[++i])
	{
		status = 1;
		if (!cmd_args[i])
			return (1);
		j = -1;
		while (cmd_args[i][++j])
		{
			if (cmd_args[i][j] == '=')
				status = 0;
			if (!ft_isalnum(cmd_args[i][j]) && cmd_args[i][j] != '='
			&& cmd_args[i][j] != '-'
			&& cmd_args[i][j] != '/'
			&& cmd_args[i][j] != ':')
				return (1);
			if (ft_isdigit(*cmd_args[i]))
				return (1);
			if (cmd_args[i][0] == '=')
				return (1);
		}
	}
	return (status);
}

void	gs_create_export(char **cmd_args, int i)
{
	char	**new_env;
	int		len;
	int		k;

	len = dp_size((g_envp));
	new_env = xmalloc((len + 2) * sizeof(char *));
	k = 0;
	while (k < len)
	{
		new_env[k] = ft_strdup(g_envp[k]);
		k++;
	}
	new_env[k++] = ft_strdup(cmd_args[i]);
	new_env[k] = NULL;
	dp_free(g_envp);
	g_envp = new_env;
}

int	gs_edit_export(char **cmd_args, char **new_split, int arg_id)
{
	char	**old_split;
	int		j;

	j = -1;
	while (g_envp[++j])
	{
		old_split = ft_split(g_envp[j], '=');
		malloc_check(old_split);
		if (!ft_strncmp(old_split[0], new_split[0],
				ft_strlen(old_split[0]) + ft_strlen(new_split[0])))
		{
			free(g_envp[j]);
			g_envp[j] = ft_strdup(cmd_args[arg_id]);
			malloc_check(g_envp[j]);
			dp_free(old_split);
			return (1);
		}
		dp_free(old_split);
	}
	return (0);
}

int	gs_export(char **cmd_args)
{
	int		i;
	char	**new_split;

	i = -1;
	if (!cmd_args[0])
		return (gs_env());
	if (gs_validate_export(cmd_args))
	{
		ft_fprintf(2, "ERROR!\n");
		return (1);
	}
	while (cmd_args[++i])
	{
		if (!cmd_args[i] || cmd_args[i][0] == 0)
		{
			ft_fprintf(2, "ERROR!\n");
			return (1);
		}
		new_split = ft_split(cmd_args[i], '=');
		malloc_check(new_split);
		if (!gs_edit_export(cmd_args, new_split, i))
			gs_create_export(cmd_args, i);
		dp_free(new_split);
	}
	return (0);
}
