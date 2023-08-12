/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:23:59 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/11 18:19:23 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

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
	int		len;
	int		i;

	i = -1;
	len = strs_len(strs);
	copy = xmalloc(sizeof(char *) * (len + 1));
	while (++i < len)
		copy[i] = ft_strdup(strs[i]);
	copy[len - 1] = NULL;
	return (copy);
}
