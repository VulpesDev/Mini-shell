/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:05:15 by lmiehler          #+#    #+#             */
/*   Updated: 2023/05/21 15:27:00 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "expander.h"
#include "libft.h"
#include "interpreter.h"
#include "utils.h"

int	ft_is_terminator(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (0);
	return (1);
}

static char	*evaluate_dollar(char *str, char **envp)
{
	char	*key;
	char	*expansion;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	if (str[i + 1] == '?' && ft_is_terminator(str[i + 2]))
	{
		expansion = ft_itoa(recent_exit_status);
		return (expansion);
	}
	if (ft_is_terminator(str[i + 1]))
		return (ft_strdup("$"));
	while (!ft_is_terminator(str[i + 1]))
		i++;
	key = ft_substr(str, 1, i);
	expansion = gs_getenv(key, envp);
	free(key);
	if (!expansion)
		return (ft_strdup(""));
	return (expansion);
}

int	contains_wildcard(char *str)
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
			if (str[i] == '*')
				return (1);
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

typedef struct s_exvar
{
	char	*ret;
	char	openq;
	int		i;
	int		j;
}t_exvar;

void	init_t(t_exvar *t)
{
	t->i = 0;
	t->j = 0;
	t->openq = 0;
	t->ret = xmalloc(10000);
}

void	dollar(char *str, char **envp, t_exvar *t)
{
	char	*exp;

	if (str[t->i] == '$')
	{
		exp = evaluate_dollar(&str[t->i], envp);
		while (!ft_is_terminator(str[t->i + 1]))
			t->i++;
		ft_memcpy((void *)&t->ret[t->j], exp, ft_strlen(exp));
		t->j += ft_strlen(exp);
		free(exp);
	}
	else
		t->ret[t->j++] = str[t->i];
}

char	*expand_variables(char *str, char **envp)
{
	t_exvar	t;

	init_t(&t);
	while (str[t.i])
	{
		if (t.openq == 0)
		{
			t.openq = is_quote(str[t.i]);
			dollar(str, envp, &t);
		}
		else
		{
			if (t.openq == is_quote(str[t.i]))
			{
				t.ret[t.j++] = str[t.i];
				t.openq = 0;
			}
			else if (t.openq == '\'')
				t.ret[t.j++] = str[t.i];
			else
				dollar(str, envp, &t);
		}
		t.i++;
	}
	t.ret[t.j] = '\0';
	return (t.ret);
}
