/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:49:45 by lmiehler          #+#    #+#             */
/*   Updated: 2023/03/17 13:36:04 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H
# include "minishell.h"

int		gs_pwd(char **cmd_args);

int		gs_cd(char	**cmd_args);

void	gs_env(char **envp);

void	gs_exit(int status);

int		gs_echo(char **cmd_args);

void	gs_export(char **cmd_args, t_meta *meta);

void	gs_unset(char **cmd_args, t_meta *meta);

#endif