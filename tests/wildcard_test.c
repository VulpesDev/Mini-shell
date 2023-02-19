/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:38:48 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/16 21:16:45 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"

int	match(char *pattern, char *str, int p, int s)
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

char	**expand_wildcards(char *str)
{
	struct dirent	*pDirent;
	DIR				*pDir;
	char			**strs;
	int				j;

	j = 0;
	strs = malloc(10000 * sizeof(char *));
	pDir = opendir(".");
	pDirent = readdir(pDir);
	while (pDirent != NULL)
	{
		if (match(str, pDirent->d_name, 0, 0))
			strs[j++] = ft_strdup(pDirent->d_name);
		pDirent = readdir(pDir);
	}
	strs[j] = NULL;
	closedir (pDir);
	return (strs);
}

int main(int argc, char **argv, char **envp)
{
	char **expanded = expand_wildcards(argv[1]);
	char **cpy = expanded;
	while (*expanded)
	{
		printf("{%s}\n", *expanded);
		expanded++;
	}
	free_strs(cpy);
}