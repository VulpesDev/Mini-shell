/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:35:50 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/14 18:00:35 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define WORD 0
# define SYMBOL 1

typedef struct s_token
{
	char *str;
	int	type;
}t_token;

typedef struct s_meta
{
	char **envp;
	int	exit_status;
	char *cmd;
	char **cmd_args;
	t_list	*tokens;
}t_meta;

#endif