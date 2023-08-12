/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:27:06 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/17 14:36:51 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

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
		{
			if (!ft_isalnum(cmd_args[i][j]) && cmd_args[i][j] != '='
			&& cmd_args[i][j] != '-'
			&& cmd_args[i][j] != '/'
			&& cmd_args[i][j] != ':')
				return (1);
			if (ft_isdigit(*cmd_args[i]))
				return (1);
		}
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
	ft_printf("No error!\n");
	return (0);
}

int	gs_remove_unset(char *str)
{
	char	**old_split;
	int		j;

	j = -1;
	while (g_envp[++j])
	{
		old_split = ft_split(g_envp[j], '=');
		malloc_check(old_split);
		if (!ft_strncmp(old_split[0], str,
				ft_strlen(old_split[0]) + ft_strlen(str)))
		{
			free(g_envp[j]);
			while (g_envp[j + 1])
			{
				g_envp[j] = g_envp[j + 1];
				j++;
			}
			g_envp[j] = NULL;
		}
		dp_free(old_split);
	}
	return (0);
}

int	gs_unset(char **cmd_args)
{
	int		i;

	if (!cmd_args[0] || gs_validate_unset(cmd_args))
		return (error(cmd_args));
	i = -1;
	while (cmd_args[++i])
		if (gs_remove_unset(cmd_args[i]))
			return (1);
	return (0);
}
