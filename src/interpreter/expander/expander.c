/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:16:54 by lmiehler          #+#    #+#             */
/*   Updated: 2023/05/01 14:34:02 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include "utils.h"
#include "lexer.h"
#include "expander.h"
#include "interpreter.h"

char	is_quote(char c)
{
	if (c == '\'')
		return ('\'');
	if (c == '\"')
		return ('\"');
	return (0);
}

char	*gs_getenv(char *str, char **envp)
{
	char	*valuestr;
	char	*env_var;
	int		i;

	valuestr = NULL;
	env_var = ft_strjoin(str, "=");
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(env_var, envp[i], ft_strlen(env_var)))
		{
			valuestr = ft_substr(envp[i], ft_strlen(env_var),
					ft_strlen(envp[i]));
			break ;
		}
		i++;
	}
	free(env_var);
	return (valuestr);
}

typedef struct s_quotevar
{
	int		i;
	int		j;
	char	openq;
	char	*ret;
}t_quotevar;

void	init_q(t_quotevar *q)
{
	q->i = 0;
	q->j = 0;
	q->openq = 0;
	q->ret = xmalloc(100000);
}

char	*remove_quotes(char *str)
{
	t_quotevar	q;

	init_q(&q);
	while (str[q.i])
	{
		if (q.openq == 0)
		{
			q.openq = is_quote(str[q.i]);
			if (q.openq == 0)
				q.ret[q.j++] = str[q.i];
		}
		else
		{
			if (q.openq == is_quote(str[q.i]))
				q.openq = 0;
			else
				q.ret[q.j++] = str[q.i];
		}
		q.i++;
	}
	q.ret[q.j] = '\0';
	free(str);
	return (q.ret);
}

Token	*expander_in(char *str, char **envp)
{
	Token	*expanded;

	expanded = NULL;
	if (!contains_wildcard(str))
	{
		str = expand_variables(str, envp);
		str = remove_quotes(str);
		token_add_back(&expanded, token_create(str));
		return (expanded);
	}
	str = expand_variables(str, envp);
	expanded = expand_wildcards(str);
	return (expanded);
}

Token	*expander(Token *commands)
{
	Token	*cur;
	Token	*expanded;

	cur = commands;
	expanded = NULL;
	while (cur)
	{
		token_add_back(&expanded, expander_in(cur->word, g_envp));
		cur = cur->next;
	}
	return (expanded);
}
