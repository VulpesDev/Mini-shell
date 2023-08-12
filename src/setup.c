/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:14:15 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/11 18:14:15 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include "signals.h"
#include "utils.h"

int	strs_len(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

char	**strs_copy(char **strs)
{
	char	**copy;
	int		i;
	int		len;

	i = -1;
	len = strs_len(strs);
	copy = xmalloc(sizeof(char *) * (len + 1));
	while (++i < len)
		copy[i] = strdup(strs[i]);
	copy[i] = NULL;
	return (copy);
}

void	setup(char **envp)
{
	g_envp = strs_copy(envp);
	init_signals();
}
