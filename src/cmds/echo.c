/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:01:16 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/13 18:38:43 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	gs_echo_print(char **strs)
{
	int i;

	i = 0;
	while (strs[i] && strs[i + 1])
	{
		ft_printf("%s ", strs[i]);
		i++;
	}
	ft_printf("%s", strs[i]);
}

void	gs_echo(char **cmd_args)
{
	if (!ft_strncmp(cmd_args[0], "-n", 3))
	{
		gs_echo_print(&cmd_args[1]);
	}
	else
	{
		gs_echo_print(&cmd_args[0]);	
		ft_printf("\n");
	}
}