/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:35:50 by lmiehler          #+#    #+#             */
/*   Updated: 2023/03/18 12:23:37 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

typedef struct s_redirection
{
	char	*file;
	int		append;
}t_redirection;

typedef struct s_code_block
{
	int				symbol;
	char			**words;
	void			*next;
}t_code_block;

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
	int				exit_status;
	char			**envp;
	char			*cmd;
	char			**cmd_args;
	t_list			*tokens;
	t_redirection	infile;
	t_redirection	outfile;
}t_meta;

void	print_tokens(t_token *tokens);

#endif