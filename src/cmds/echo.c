/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:01:16 by lmiehler          #+#    #+#             */
/*   Updated: 2023/03/25 02:02:21 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/////!echo without args is seg fault
void	gs_echo_print(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] && strs[i + 1])
	{
		ft_printf("%s ", strs[i]);
		i++;
	}
	ft_printf("%s", strs[i]);
}

int	gs_echo(char **cmd_args)
{
	if (!*cmd_args)
	{
		ft_printf("\n");
	}
	else if (!ft_strncmp(cmd_args[0], "-n", 3))
	{
		gs_echo_print(&cmd_args[1]);
	}
	else
	{
		gs_echo_print(&cmd_args[0]);
		ft_printf("\n");
	}
	return (0);
}