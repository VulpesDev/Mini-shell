/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:33:29 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/26 15:39:20 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "libft.h"
#include "utils.h"
#include <stdlib.h>

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

int	gs_remove_unset(char **envp, char *str)
{
	char	**old_split;
	int		j;

	j = -1;
	while (envp[++j])
	{
		old_split = ft_split(envp[j], '=');
		malloc_check(old_split);
		if (!ft_strncmp(old_split[0], str,
				ft_strlen(old_split[0]) + ft_strlen(str)))
		{
			free(envp[j]);
			while (envp[j + 1])
			{
				envp[j] = envp[j + 1];
				j++;
			}
			envp[j] = NULL;
		}
		dp_free(old_split);
	}
	return (0);
}

void	gs_unset(char **cmd_args, char **envp)
{
	int		i;

	if (!cmd_args[0])
		ft_fprintf(2, "unset: not enough arguments\n");
	if (gs_validate_unset(cmd_args))
		ft_fprintf(2, "ERROR!\n");
	i = -1;
	while (cmd_args[++i])
		gs_remove_unset(envp, cmd_args[i]);
}
