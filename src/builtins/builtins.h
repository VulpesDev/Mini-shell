/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:25:41 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/17 13:10:45 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "../../libft/include/libft.h"
# include "../minishell.h"
# include "expander.h"
# include <stdlib.h>
# include <unistd.h>
# define PWD_SIZE 10000

int		gs_env(void);

void	gs_exit(int status);

int		gs_cd(char	**cmd_args);

int		gs_echo(char **cmd_args);

int		gs_pwd(char **cmd_args);

int		gs_export(char **cmd_args);

int		gs_unset(char **cmd_args);

//Utils
void	print_strs(char *str[]);
int		dp_size(char **str);
void	*xmalloc(size_t size);
void	malloc_check(void *p);
void	dp_free(char **str);
char	**dp_cpy(char **str);

#endif