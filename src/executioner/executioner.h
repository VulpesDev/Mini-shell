/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executioner.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:15:20 by lmiehler          #+#    #+#             */
/*   Updated: 2023/03/17 15:46:41 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTIONER_H
# define EXECUTIONER_H

# include "minishell.h"

int	exec_cmd(t_meta *meta);

typedef struct s_vars
{
	int		i;
	int		child_pid;
	int		child_status;
	char	*path_cmd;
	char	**paths;
}t_vars;

char	**get_paths(char **envp);

int	executioner(t_code_block *blocks, t_meta *meta);

#endif