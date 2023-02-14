/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:38:16 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/14 13:14:58 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include "cmds.h"

//? Add a return value to the executioner
void	executioner(t_meta *meta)
{
	if (meta->cmd == NULL)
		return ;
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
	else if (!ft_strncmp("pwd", meta->cmd, 4))
	{
		gs_pwd(meta);
	}
	else if (!ft_strncmp("cd", meta->cmd, 4))
	{
		gs_cd(meta);
	}
}