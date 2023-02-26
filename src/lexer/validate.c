/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:01:26 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/26 21:56:10 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(void)
{
	ft_printf("SYMBOL ERROR!\n");
	return (0);
}

int	validate(t_code_block *blocks)
{
	t_code_block	*b;
	t_code_block	*nextb;
	int				l_sym;
	char			*last_sym;
	int				open_brack;
	int				close_brack;

	last_sym = 0;
	l_sym = 0;
	b = blocks;
	open_brack = 0;
	close_brack = 0;
	while (b)
	{
		if (b->symbol)
		{
			if (!ft_strncmp(b->words[0], "&", 1) || !ft_strncmp(b->words[0], "|", 1))
			{
				nextb = b->next;
				if (!nextb || (nextb->symbol && ft_strncmp(nextb->words[0], "<", 1) && ft_strncmp(nextb->words[0], ">", 1) && ft_strncmp(nextb->words[0], "(", 1)))
					return (print_error());
			}
		}
		if (!ft_strncmp(b->words[0], "(", 1))
			open_brack++;
		else if (!ft_strncmp(b->words[0], ")", 1))
			close_brack++;
		if (l_sym)
		{
			if (ft_strncmp(last_sym, "(", 1) && ft_strncmp(last_sym, ")", 1) && !ft_strncmp(last_sym, b->words[0], 1))
				return (print_error());
			else if ((!ft_strncmp(last_sym, "(", 1) || !ft_strncmp(last_sym, "&", 1)) && (!ft_strncmp(b->words[0], "|", 1)))
				return (print_error());
			else if ((!ft_strncmp(last_sym, "(", 1) || !ft_strncmp(last_sym, "|", 1)) && (!ft_strncmp(b->words[0], "&", 1)))
				return (print_error());
			else if ((!ft_strncmp(last_sym, "(", 1) || !ft_strncmp(last_sym, "&", 1)) && (!ft_strncmp(b->words[0], "|", 1)))
				return (print_error());
			else if ((!ft_strncmp(last_sym, "(", 1) || !ft_strncmp(last_sym, "&", 1) || !ft_strncmp(last_sym, "|", 1)) && (!ft_strncmp(b->words[0], ")", 1)))
				return (print_error());
			else if ((!ft_strncmp(last_sym, ")", 1)) && (!ft_strncmp(b->words[0], "(", 1)))
				return (print_error());
		}
		last_sym = b->words[0];
		l_sym = b->symbol;
		b = b->next;
	}
	if (open_brack != close_brack)
		return (print_error());
	return (1);
}