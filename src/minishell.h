/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:35:50 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/26 18:34:21 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# define DOC_NAME "here_doc"

typedef struct s_redirection
{
	char	*file;
	int		append;
}t_redirection;

typedef struct s_code_block
{
	int					symbol;
	char				**words;
	struct s_code_block	*next;
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
	int				last_exit_status;
	int				exit_status;
	char			**envp;
	char			*cmd;
	char			**cmd_args;
	t_redirection	infile;
	t_redirection	outfile;
	t_token			*tokens;
	t_code_block	*blocks;
}t_meta;

void	create_here_doc(char *limiter);

#endif