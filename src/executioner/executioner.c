/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:38:16 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/13 18:36:57 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "cmds.h"

void executioner(t_meta *meta)
{
	if (!ft_strncmp("env", meta->cmd, 4))
	{
		gs_env(meta->envp);
	}
	else if (!ft_strncmp("exit", meta->cmd, 5))
	{
		gs_exit(meta->exit_status);
	}
	else if (!ft_strncmp("echo", meta->cmd, 5))
	{
		gs_echo(meta->cmd_args);
	}
}