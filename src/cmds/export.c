/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:33:32 by lmiehler          #+#    #+#             */
/*   Updated: 2023/03/28 12:08:59 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "libft.h"
#include "utils.h"
#include <stdlib.h>

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

	k = 0;
	len = dp_size((meta->envp));
	new_env = xmalloc(len * sizeof(char *) + 2);
	while (k < len)
	{
		new_env[k] = ft_strdup(meta->envp[k]);
		k++;
	}
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
