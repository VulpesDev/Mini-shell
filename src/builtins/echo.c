/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:24:11 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/24 17:32:00 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	validate_n(char *cmd_arg)
{
	int	i;

	i = 0;
	if (*cmd_arg == '-')
	{
		i++;
		while (cmd_arg[i])
		{
			if (cmd_arg[i] == 'n')
				i++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

int	n_option_pos(char **cmd_args)
{
	int	result;

	result = 0;
	while (cmd_args[result])
	{
		if (validate_n(cmd_args[result]))
			result++;
		else
			break ;
	}
	return (result);
}

void	gs_echo_print(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && strs[i + 1])
	{
		ft_printf("%s ", strs[i]);
		i++;
	}
	ft_printf("%s", strs[i] ? strs[i] : "");
}

int	gs_echo(char **cmd_args)
{
	if (!*cmd_args)
	{
		ft_printf("\n");
	}
	else if (validate_n(*cmd_args))
	{
		gs_echo_print(&cmd_args[n_option_pos(cmd_args)]);
	}
	else
	{
		gs_echo_print(&cmd_args[0]);
		ft_printf("\n");
	}
	return (0);
}
