/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 13:31:25 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/14 19:48:16 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "utils.h"

char **lexical_split(char *str)
{
	int i;
	int	word_start;

	word_start = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			ft_substr(str, word_start, i - word_start);
			word_start = i + 1;
		}
		word_start++;
		i++;
	}
}

void	lexer(t_meta *meta, const char *str)
{
	t_list *tokens;
}