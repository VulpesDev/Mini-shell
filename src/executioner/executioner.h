/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:15:20 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/26 16:52:29 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTIONER_H
# define EXECUTIONER_H

# include "minishell.h"

int		exec_cmd(char *cmd, char **cmd_args, char **envp);

char	**get_paths(char **envp);

typedef struct s_vars
{
	int		i;
	int		child_pid;
	int		child_status;
	char	*path_cmd;
	char	**paths;
}t_vars;

#endif