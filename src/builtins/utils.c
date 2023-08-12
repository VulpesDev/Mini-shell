/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:26:15 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/07 13:55:16 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <stdio.h>

void	print_strs(char *str[])
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
}

int	dp_size(char **str)
{
	int	result;

	result = 0;
	while (str[result])
		result++;
	return (result);
}

void	malloc_check(void *p)
{
	if (p == NULL)
	{
		ft_fprintf(2, "Malloc failed\n");
		exit(1);
	}
}

void	dp_free(char **str)
{
	int	len;

	len = dp_size(str);
	while (--len + 1)
	{
		free(str[len]);
	}
	free(str);
}

char	**dp_cpy(char **str)
{
	char	**result;
	int		len;
	int		i;

	i = -1;
	len = dp_size(str);
	result = xmalloc((len + 1) * sizeof(char *));
	while (++i < len)
		result[i] = ft_strdup(str[i]);
	result[i] = 0;
	return (result);
}
