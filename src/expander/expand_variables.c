/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:05:15 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/19 15:11:36 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include "utils.h"

// Check header for description

static char	*evaluate_dollar(char *str, char **envp)
{
	char	*key;
	char	*expansion;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	if (str[i + 1] == '\0' || ft_isspace(str[i + 1]) || str[i + 1] == '$')
		return (ft_strdup("$"));
	while (str[i + 1] && str[i + 1] != '$' && !ft_isspace(str[i + 1]))
		i++;
	key = ft_substr(str, 1, i);
	malloc_check(key);
	expansion = gs_getenv(key, envp);
	free(key);
	if (!expansion)
		return (ft_strdup(""));
	return (expansion);
}

char *expand_variables(char *str, char **envp)
{
	char	*ret;
	char	*exp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	ret = xmalloc(100000);
	while (str[i])
	{
		if (str[i] == '$')
		{
			exp = evaluate_dollar(&str[i], envp);
			while (str[i + 1] && str[i + 1] != '$' && !ft_isspace(str[i + 1]))
				i++;
			ft_memcpy((void *)&ret[j], exp, ft_strlen(exp));
			j += ft_strlen(exp);
			free(exp);
		}
		else
			ret[j++] = str[i];
		i++;
	}
	ret[j] = '\0';
	return (ret);
}