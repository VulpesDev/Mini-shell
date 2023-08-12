/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:36:07 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/06 16:39:59 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H
# include "minishell.h"
# include "libft.h"

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define HEREDOC_NAME "__________heredoc4847921478921789412"

typedef struct s_Redirection
{
	enum	RedirectionType
	{
		REDIR_IN,
		REDIR_OUT,
		REDIR_APPEND,
		REDIR_HEREDOC
	}						type;
	char					*str;
	struct s_Redirection	*next;
}t_Redirection;

int				parse_tok_redir(Token *token_lst, int stdin_fd);

int				parse_redirections(t_Redirection *redir_lst);

t_Redirection	*redir_create(void *content, int type);

t_Redirection	*redir_last(t_Redirection *lst);

void			redir_add_back(t_Redirection **lst, t_Redirection *new_elem);

void	redir_free(t_Redirection *lst);

#endif