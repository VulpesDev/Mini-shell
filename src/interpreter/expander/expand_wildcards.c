/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcards.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:20:00 by lmiehler          #+#    #+#             */
/*   Updated: 2023/05/06 15:38:12 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include "libft.h"
#include "utils.h"
#include "minishell.h"
#include "expander.h"
#include "lexer.h"

int	is_oc_quote(char *str, int index)
{
	int		i;
	char	openq;

	i = 0;
	openq = 0;
	while (str[i])
	{
		if (openq == 0)
		{
			openq = is_quote(str[i]);
			if (openq && i == index)
				return (1);
		}
		else
		{
			if (openq == is_quote(str[i]))
			{
				if (i == index)
					return (1);
				openq = 0;
			}
		}
		i++;
	}
	return (0);
}

int	is_quoted(char *str, int index)
{
	int		i;
	char	openq;

	i = 0;
	openq = 0;
	while (str[i])
	{
		if (i == index)
			return (openq);
		if (openq == 0)
		{
			openq = is_quote(str[i]);
		}
		else
		{
			if (openq == is_quote(str[i]))
				openq = 0;
		}
		i++;
	}
	return (0);
}

static int	match(char *pattern, char *str, int p, int s)
{
	if (pattern[p] == '\0')
		return (str[s] == '\0');
	if (is_oc_quote(pattern, p))
		return (match(pattern, str, p + 1, s));
	else if (pattern[p] == '*' && !is_quoted(pattern, p))
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

Token	*expand_wildcards(char *pattern)
{
	struct dirent	*dirent;
	DIR				*dir;
	Token			*expanded;

	expanded = NULL;
	dir = opendir(".");
	dirent = readdir(dir);
	while (dirent != NULL)
	{
		if (match(pattern, dirent->d_name, 0, 0))
			token_add_back(&expanded, token_create(ft_strdup(dirent->d_name)));
		dirent = readdir(dir);
	}
	closedir (dir);
	free(pattern);
	return (expanded);
}
