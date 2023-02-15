/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:33:32 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/15 16:14:24 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmds.h"
#include "libft.h"
#include "utils.h"
#include <stdlib.h>

//? Validate input
//TODO Compare the string before = sign
//TODO if it exists, replace the value
//TODO if it doesn't exist create a new one
//? when more than one equal sign, problems
int	gs_validate(char **cmd_args)
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

void	gs_export(char **cmd_args, t_meta *meta)
{
	int	i;
	int	j;
	char	**split;
	char	**new_split;
	int	found;

	i = -1;
	if (gs_validate(cmd_args))
		ft_printf("ERROR!\n");
	while (cmd_args[++i])
	{
		j = -1;
		found = 0;
		new_split = ft_split(cmd_args[i], '='); //!not protected
		while (meta->envp[++j])
		{
			split = ft_split(meta->envp[j], '='); //!not protected
			if (!ft_strncmp(split[0], new_split[0], ft_strlen(split[0]) + ft_strlen(new_split[0])))
			{
				free(meta->envp[j]);
				meta->envp[j] = ft_strdup(cmd_args[i]);
				if (!meta->envp[j])
				{
					ft_fprintf(2, "Malloc failed\n");
					exit(1);
				}
				found = 1;
				break ;
			}
			free(split);//! should free everything inside split
		}
		if (!found)
		{
			char	**new_env;
			int		len;
			int		k;

			k = 0;
			len = size_dp((meta->envp));
			new_env = xmalloc(len * sizeof(char*) + 2);
			while (k < len - 1)
			{
				new_env[k] = ft_strdup(meta->envp[k]);
				k++;
			}
			new_env[k++] = ft_strdup(cmd_args[i]);
			new_env[k] = NULL;
			free(meta->envp);
			meta->envp = new_env;
		}
	}
	//?if new_split fails, should still free split
	free(new_split);//! should free everything inside split
}