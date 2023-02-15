/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:49:45 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/15 10:42:30 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H
# include "minishell.h"

void	gs_env(char **envp);

void	gs_exit(int status);

void	gs_echo(char **str);

int		gs_pwd(t_meta *meta);

int		gs_cd(t_meta *meta);

void	gs_export(char **cmd_args, t_meta *meta);

#endif