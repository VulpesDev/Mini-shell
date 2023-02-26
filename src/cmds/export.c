/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:33:32 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/26 15:39:52 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "libft.h"
#include "utils.h"
#include <stdlib.h>

//? Validate input
/////TODO Compare the string before = sign
/////TODO if it exists, replace the value
/////TODO if it doesn't exist create a new one
/////TODO export without arguments displays env
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
void	gs_create_export(char **cmd_args, char **envp, int i)
{
	char	**new_env;
	int		len;
	int		k;

	k = 0;
	len = dp_size((envp));
	new_env = xmalloc(len * sizeof(char *) + 2);
	while (k < len)
	{
		new_env[k] = ft_strdup(envp[k]);
		k++;
	}
	new_env[k++] = ft_strdup(cmd_args[i]);
	new_env[k] = NULL;
	free(envp);
	envp = new_env;
}

//Edits export dp Returns found(bool)
int	gs_edit_export(char **cmd_args, char **envp, char **new_split, int i)
{
	char	**old_split;
	int		j;

	j = -1;
	while (envp[++j])
	{
		old_split = ft_split(envp[j], '=');
		malloc_check(old_split);
		if (!ft_strncmp(old_split[0], new_split[0],
				ft_strlen(old_split[0]) + ft_strlen(new_split[0])))
		{
			free(envp[j]);
			envp[j] = ft_strdup(cmd_args[i]);
			malloc_check(envp[j]);
			return (1);
		}
		dp_free(old_split);
	}
	return (0);
}

void	gs_export(char **cmd_args, char **envp)
{
	int		i;
	char	**new_split;
	int		found;

	i = -1;
	if (!cmd_args[0])
		gs_env(envp);
	if (gs_validate_export(cmd_args))
		ft_fprintf(2, "ERROR!\n");
	while (cmd_args[++i])
	{
		found = 0;
		new_split = ft_split(cmd_args[i], '=');
		malloc_check(new_split);
		if (!gs_edit_export(cmd_args, envp, new_split, i))
			gs_create_export(cmd_args, envp, i);
		dp_free(new_split);
	}
}
