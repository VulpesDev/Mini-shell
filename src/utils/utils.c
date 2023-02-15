/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:18:24 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/15 16:58:44 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	malloc_check(void *p)
{
	if (p == NULL)
	{
		ft_fprintf(2, "Malloc failed\n");
		exit(1);
	}
}

void	*xmalloc(size_t size)
{
	void *p;

	p = malloc(size);
	if (!p)
	{
		ft_fprintf(2, "Malloc failed\n");
		exit(1);
	}
	return (p);
}

int	dp_size(char **str)
{
	int	result;

	result = 0;
	while (str[result])
		result++;
	return (result);
}

int	dp_free(char **str)
{
	int	result;

	result = 0;
	while (str[result])
		result++;
	return (result);
}

char	**dp_cpy(char **str)
{
	char	**result;
	int		len;
	int		i;

	i = -1;
	len = dp_size(str);
	result = xmalloc(len * sizeof(char *) + 1);
	while (++i < len)
		result[i] = ft_strdup(str[i]);
	return (result);
}

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