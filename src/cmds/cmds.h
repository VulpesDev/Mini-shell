/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:49:45 by lmiehler          #+#    #+#             */
/*   Updated: 2023/03/24 20:51:05 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H
# include "minishell.h"

int		gs_pwd(char **cmd_args);

int		gs_cd(char	**cmd_args);

int	gs_env(char **envp);

int	gs_exit(int status);

int		gs_echo(char **cmd_args);

int	gs_export(char **cmd_args, t_meta *meta);

int	gs_unset(char **cmd_args, t_meta *meta);

#endif