/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:01:26 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/26 18:49:20 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate(t_code_block *blocks)
{
	t_code_block	*b;
	int				l_sym;
	char			*last_sym;

	last_sym = 0;
	l_sym = 0;
	b = blocks;
	while (b)
	{
		if (l_sym)
		{
			if (!ft_strncmp(last_sym, b->words[0], 1))
				ft_printf("SYMBOL ERROR!\n");
			else if ((!ft_strncmp(last_sym, "(", 1) || !ft_strncmp(last_sym, "&", 1)) && (!ft_strncmp(b->words[0], "|", 1)))
				ft_printf("SYMBOL ERROR!\n");
			else if ((!ft_strncmp(last_sym, "(", 1) || !ft_strncmp(last_sym, "|", 1)) && (!ft_strncmp(b->words[0], "&", 1)))
				ft_printf("SYMBOL ERROR!\n");
			else if ((!ft_strncmp(last_sym, "(", 1) || !ft_strncmp(last_sym, "&", 1)) && (!ft_strncmp(b->words[0], "|", 1)))
				ft_printf("SYMBOL ERROR!\n");
			else if ((!ft_strncmp(last_sym, "(", 1) || !ft_strncmp(last_sym, "&", 1) || !ft_strncmp(last_sym, "|", 1)) && (!ft_strncmp(b->words[0], ")", 1)))
				ft_printf("SYMBOL ERROR!\n");
			else if ((!ft_strncmp(last_sym, ")", 1)) && (!ft_strncmp(b->words[0], "(", 1)))
				ft_printf("SYMBOL ERROR!\n");
		}
		last_sym = b->words[0];
		l_sym = b->symbol;
		b = b->next;
	}
	return (1);
}