/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:18:24 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/16 20:25:00 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char *gs_getenv(char *str, char **envp)
{
	char	*valuestr;
	char	*env_var;
	int	i;

	valuestr = NULL;
	env_var = ft_strjoin(str, "=");
	malloc_check((void *)env_var);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(env_var, envp[i], ft_strlen(env_var)))
		{
			valuestr = ft_substr(envp[i], ft_strlen(env_var), ft_strlen(envp[i]));
			malloc_check((void *)valuestr);
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