/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:49:45 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/14 12:22:41 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDS_H
# define CMDS_H

void gs_env(char **envp);

void gs_exit(int status);

void gs_echo(char **str);

void	gs_pwd(void);

int	gs_cd(const char *path);

#endif