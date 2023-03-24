/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:33:29 by lmiehler          #+#    #+#             */
/*   Updated: 2023/03/17 13:35:46 by tvasilev         ###   ########.fr       */
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

void	gs_unset(char **cmd_args, t_meta *meta)
{
	int		i;

	if (!cmd_args[0])
		ft_fprintf(2, "unset: not enough arguments\n");
	if (gs_validate_unset(cmd_args))
		ft_fprintf(2, "ERROR!\n");
	i = -1;
	while (cmd_args[++i])
		gs_remove_unset(meta, cmd_args[i]);
}
