/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:31:25 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/25 14:31:41 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "utils.h"
#include "expander.h"

/*lexer takes the str passed by readline
and creates tokens out of it. The return value
is either NULL in case of error or the token list.*/

void	expand_token(t_token **lst, char *str, char type, char **envp)
{
	//ft_printf("hrer\n");
	//ft_printf("str = %s\n", str);
	int		i;
	char	**strs;

	if (type == 's')
	{
		//ft_printf("is symbol str = %s\n", str);
		token_add_back(lst, token_new(ft_strdup(str), 's'));
		return ;
	}
	strs = expander(str, envp);
	//print_strs(strs);
	i = 0;
	while(strs[i])
	{
		token_add_back(lst, token_new(ft_strdup(strs[i]), 'w'));
		i++;
	}
	free_strs(strs);
	//ft_printf("end\n");
}

t_token *expand_tokens(t_token **tk, char **envp)
{
	t_token	*lst;
	t_token	*cur;

	cur = *tk;
	lst = NULL;
	while (cur != NULL)
	{
		expand_token(&lst, cur->str, cur->type, envp);
		cur = cur->next;
	}
	token_clear(tk);
	return (lst);
}

t_token	*lexer(char *str, char **envp)
{
	t_token	*tokens;
	char	**r;
	char	**r2;
	char	*set;
	int		i_s[2];

	tokens = 0;
	set = ft_strdup("<>|&()");
	r = lexical_split(str);
	i_s[0] = -1;
	while (r[++i_s[0]])
	{
		r2 = symbolical_split(r[i_s[0]], set);
		i_s[1] = -1;
		while (r2[++i_s[1]])
			if (ft_strchr(set, (int)*r2[i_s[1]]))
				token_add_back(&tokens, token_new(ft_strdup(r2[i_s[1]]), 's'));
		else
			token_add_back(&tokens, token_new(ft_strdup(r2[i_s[1]]), 'w'));
		dp_free(r2);
	}
	free(set);
	dp_free(r);
	return (expand_tokens(&tokens, envp));
}
