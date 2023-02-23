/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:49:45 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/21 15:41:47 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H
# include "minishell.h"

int		gs_pwd(t_meta *meta);
int		gs_cd(t_meta *meta);
void	gs_env(char **envp);
void	gs_exit(int status);
void	gs_echo(char **str);
void	gs_export(char **cmd_args, t_meta *meta);
void	gs_unset(char **cmd_args, t_meta *meta);

#endif