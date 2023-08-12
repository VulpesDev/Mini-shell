/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:21:15 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/21 15:29:07 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>

char	*ft_strncpy(char *src, int len)
{
	int		i;
	char	*result;

	i = 0;
	result = xmalloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (i < len && src[i])
	{
		result[i] = src[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n && *s1 && (*s1 == *s2))
	{
		++s1;
		++s2;
		--n;
	}
	if (n == 0)
		return (0);
	else
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ptr;
	char	*i;

	len = ft_strlen(s) + 1;
	ptr = xmalloc(sizeof(*ptr) * len);
	i = ptr;
	if (ptr == NULL)
		return (NULL);
	while (*s)
		*i++ = *s++;
	*i = '\0';
	return (ptr);
}


size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (s == NULL)
		return (0);
	len = 0;
	while (*s)
	{
		len++;
		s++;
	}
	return (len);
}