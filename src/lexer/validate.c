/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 17:01:26 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/27 13:27:41 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"

int	check_bracks(t_token *blocks)
{
	t_token	*b;
	int		bracks;

	b = blocks;
	bracks = 0;
	while (b)
	{
		if (!ft_strncmp(b->str, "(", 1))
			bracks++;
		else if (!ft_strncmp(b->str, ")", 1))
			bracks--;
		if (bracks < 0)
			return (0);
		b = b->next;
	}
	if (bracks)
		return (0);
	return (1);
}

int	check_lsymb(char *last_sym, t_token *b)
{
	if (ft_strncmp(last_sym, "(", 1) && ft_strncmp(last_sym, ")", 1)
		&& !ft_strncmp(last_sym, b->str, 1))
		return (0);
	else if ((!ft_strncmp(last_sym, "(", 1)
			|| !ft_strncmp(last_sym, "&", 1))
		&& (!ft_strncmp(b->str, "|", 1)))
		return (0);
	else if ((!ft_strncmp(last_sym, "(", 1)
			|| !ft_strncmp(last_sym, "|", 1))
		&& (!ft_strncmp(b->str, "&", 1)))
		return (0);
	else if ((!ft_strncmp(last_sym, "(", 1)
			|| !ft_strncmp(last_sym, "&", 1))
		&& (!ft_strncmp(b->str, "|", 1)))
		return (0);
	else if ((!ft_strncmp(last_sym, "(", 1)
			|| !ft_strncmp(last_sym, "&", 1)
			|| !ft_strncmp(last_sym, "|", 1))
		&& (!ft_strncmp(b->str, ")", 1)))
		return (0);
	else if ((!ft_strncmp(last_sym, ")", 1))
		&& (!ft_strncmp(b->str, "(", 1)))
		return (0);
	return (1);
}

int	check_symb(t_token *b)
{
	t_token	*nextb;

	nextb = b->next;
	if (!ft_strncmp(b->str, "&", 1)
		|| !ft_strncmp(b->str, "|", 1))
	{
		if (!nextb || (nextb->type == 's'
				&& ft_strncmp(nextb->str, "<", 1)
				&& ft_strncmp(nextb->str, ">", 1)
				&& ft_strncmp(nextb->str, "(", 1)))
			return (0);
	}
	if (!ft_strncmp(b->str, "<", 1)
		|| !ft_strncmp(b->str, ">", 1))
	{
		if (!nextb || nextb->type == 's')
			return (0);
	}
	return (1);
}

int	check_word(t_token *b)
{
	t_token	*nextb;

	nextb = b->next;
	if (nextb)
		if (!ft_strncmp(nextb->str, "(", 1))
			return (0);
	return (1);
}

int	validate(t_token *blocks)
{
	t_token	*b;
	int		l_sym;
	char	*last_sym;

	last_sym = 0;
	l_sym = 0;
	b = blocks;
	while (b)
	{
		if (b->type == 's')
			if (!check_symb(b))
				return (print_error());
		if (b->type == 'w')
			if (!check_word(b))
				return (print_error());
		if (l_sym)
			if (!check_lsymb(last_sym, b))
				return (print_error());
		last_sym = b->str;
		l_sym = b->type == 's';
		b = b->next;
	}
	if (!check_bracks(blocks))
		return (print_error());
	return (1);
}
