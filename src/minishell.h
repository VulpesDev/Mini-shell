/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:35:50 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/21 13:22:40 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

/*str is the content.
type could be either 's' or 'w'
for symbol or word*/
typedef struct s_token
{
	char	*str;
	char	type;
	void	*next;
}t_token;

typedef struct s_meta
{
	char	**envp;
	int		exit_status;
	char	*cmd;
	char	**cmd_args;
	t_list	*tokens;
}t_meta;

#endif