/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:16:54 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/23 18:12:41 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include "utils.h"
#include "expander.h"

typedef struct s_quotevar
{
	int	i;
	int	j;
	char openq;
	char *ret;
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
	t_quotevar q;

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

char	**expander(char *str, char **envp)
{
	char	**expansions;

	if (!contains_wildcard(str))
	{
		str = expand_variables(str, envp);
		expansions = xmalloc(2 * sizeof(char *));
		expansions[0] = remove_quotes(str);
		expansions[1] = NULL;
		return (expansions);
	}
	ft_printf("does contain wildcard\n");
	str = expand_variables(str, envp);
	ft_printf("exvar = {%s}\n", str);
	expansions = expand_wildcards(str);
	ft_printf("expander finished\n");
	return (expansions);
}