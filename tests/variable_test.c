/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:19:26 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/19 15:04:02 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
char *gs_getenv(char *str, char **envp)
{
	char	*valuestr;
	char	*env_var;
	int	i;

	valuestr = NULL;
	env_var = ft_strjoin(str, "=");
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(env_var, envp[i], ft_strlen(env_var)))
		{
			valuestr = ft_substr(envp[i], ft_strlen(env_var), ft_strlen(envp[i]));
			break ;
		}
		i++;
	}
	free(env_var);
	return (valuestr);
}

int ft_isspace(char c)
{
	if (c == ' '
		|| c == '\f'
		|| c == '\n'
		|| c == '\r'
		|| c == '\t'
		|| c == '\v')
	{
		return (1);
	}
	return (0);
}

char *evaluate_dollar(char *str, char **envp)
{
	printf("str = %s\n", str);
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
	printf("key = %s\n", key);
	expansion = gs_getenv(key, envp);
	free(key);
	if (!expansion)
		return (ft_strdup(""));
	return (expansion);
}

char *expand_variables(char *str, char **envp)
{
	char *ret;
	char *exp;
	int i;
	int j;
	j = 0;
	i = 0;

	ret = malloc(100000);
	while (str[i])
	{
		if (str[i] == '$')
		{
			exp = evaluate_dollar(&str[i], envp);
			while (str[i + 1] && str[i + 1] != '$' && !ft_isspace(str[i + 1]))
				i++;
			ft_memcpy((void *)&ret[j], exp, ft_strlen(exp));
			j += ft_strlen(exp);
		}
		else
			ret[j++] = str[i];
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

int main(int argc, char **argv, char **envp)
{
	printf("OUT = {%s}\n", expand_variables(argv[1], envp));
}