/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:25:18 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/17 14:21:00 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	gs_chdir_protect_no_free(char	*path)
{
	if (chdir(path))
	{
		ft_fprintf(2, "cd: no such file or directory: %s\n", path);
		return (1);
	}
	return (0);
}

int	gs_chdir_protect(char	*path)
{
	if (chdir(path))
	{
		ft_fprintf(2, "cd: no such file or directory: %s\n", path);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}

int	gs_cd(char	**cmd_args)
{
	if (cmd_args[0] && cmd_args[1])
	{
		ft_fprintf(2, "cd: too many arguments\n");
		return (1);
	}
	else if (!cmd_args[0])
		return (gs_chdir_protect(gs_getenv("HOME", g_envp)));
	else if (!ft_strncmp("~", cmd_args[0], 2))
		return (gs_chdir_protect(gs_getenv("HOME", g_envp)));
	else
		return (gs_chdir_protect_no_free(cmd_args[0]));
}
