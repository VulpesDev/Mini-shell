/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 14:53:12 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/26 16:55:28 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include <stdlib.h>

char	**get_paths(char **envp)
{
	int		i;
	char	*temp;
	char	*path;
	char	**result;

	path = gs_getenv("PATH", envp);
	result = ft_split(path, ':');
	i = -1;
	while (result[++i])
	{
		temp = ft_strdup(result[i]);
		free(result[i]);
		result[i] = ft_strjoin(temp, "/");
		free(temp);
	}
	return (result);
}
