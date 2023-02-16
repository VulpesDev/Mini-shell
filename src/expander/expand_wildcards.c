/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:20:00 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/16 20:39:16 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"
#include "utils.h"

// Check header for description

static int	match(char *pattern, char *str, int p, int s)
{
	if (pattern[p] == '\0')
		return (str[s] == '\0');
	else if (pattern[p] == '*')
	{
		while (str[s])
		{
			if (match(pattern, str, p + 1, s))
				return (1);
			s++;
		}
		return (match(pattern, str, p + 1, s));
	}
	else if (pattern[p] != str[s])
		return (0);
	else
		return (match(pattern, str, p + 1, s + 1));
}

char	**expand_wildcards(char *pattern)
{
	struct dirent	*dirent;
	DIR				*dir;
	char			**strs;
	int				j;

	j = 0;
	strs = xmalloc(10000 * sizeof(char *));
	dir = opendir(".");
	dirent = readdir(dir);
	while (dirent != NULL)
	{
		if (match(pattern, dirent->d_name, 0, 0))
		{
			strs[j++] = ft_strdup(dirent->d_name);
			malloc_check(strs[j - 1]);
		}
		dirent = readdir(dir);
	}
	strs[j] = NULL;
	closedir (dir);
	return (strs);
}