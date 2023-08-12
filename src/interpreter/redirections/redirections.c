/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:38:04 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/17 14:27:20 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "redirections.h"
#include "libft.h"
#include "get_next_line.h"

int g_stdin;

typedef struct s_fds
{
	int	fd_in;
	int	fd_out;
	int	fd_append;
	int	fd_heredoc;
} t_fds;

typedef struct s_fdNames
{
	char	*fd_in;
	char	*fd_out;
	char	*fd_append;
	char	*fd_heredoc;
} t_fdNames;

void init_fd(t_fds *fd)
{
	fd->fd_in = -2;
	fd->fd_out = -2;
	fd->fd_append = -2;
	fd->fd_heredoc = -2;
}
void init_fdNames(t_fdNames *fdNames)
{
	fdNames->fd_in = NULL;
	fdNames->fd_out = NULL;
	fdNames->fd_append = NULL;
	fdNames->fd_heredoc = NULL;
}

void	determine_redirections(t_fdNames *fdNames, t_Redirection *redir_lst)
{
	while (redir_lst)
	{
		if (redir_lst->type == REDIR_IN)
			fdNames->fd_in = redir_lst->str;
		else if (redir_lst->type == REDIR_OUT)
		{
			fdNames->fd_out = redir_lst->str;
			fdNames->fd_append = NULL;
		}
		else if (redir_lst->type == REDIR_APPEND)
		{
			fdNames->fd_append = redir_lst->str;
			fdNames->fd_out = NULL;
		}
		else if (redir_lst->type == REDIR_HEREDOC)
			fdNames->fd_heredoc = redir_lst->str;
		redir_lst = redir_lst->next;
	}
}

int	heredoc_func(int fd, char *heredoc_str)
{
	char	*line;
	
	dup2(g_stdin, 0);
	line = NULL;
	do
	{
		fprintf(stderr, "heredoc> ");
		if (line)
			free(line);
		line = get_next_line(0);
		if (!line)
			return (0);
		line[ft_strlen(line) - 1] = '\0';
		if (!ft_strncmp(line, heredoc_str, ft_strlen(heredoc_str) + ft_strlen(line)))
			break ;
		if (write(fd, line, ft_strlen(line)) == -1)
		{
			free(line);
			return (1);
		}
		if (write (fd, "\n", 1) == -1)
		{
			free(line);
			return (1);
		}
	}
	while (ft_strncmp(line, heredoc_str, ft_strlen(heredoc_str) + ft_strlen(line)));
	return (0);
}

int	act_redirections(t_fds *fd, t_fdNames fdNames)
{
	if (fdNames.fd_in)
	{
		fd->fd_in = open(fdNames.fd_in, O_RDONLY, 0777);
		if (fd->fd_in == -1) {
			fprintf(stderr, "[Error]: Redirection failed\n");
			return 0;
		}
	}
	if (fdNames.fd_out)
	{
		fd->fd_out = open(fdNames.fd_out, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (fd->fd_out == -1) {	
			fprintf(stderr, "[Error]: Redirection failed\n");
			return 0;
		}
	}
	if (fdNames.fd_append)
	{
		fd->fd_append = open(fdNames.fd_append, O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (fd->fd_append == -1) {
			fprintf(stderr, "[Error]: Redirection failed\n");
			return 0;
		}
	}
	if (fdNames.fd_heredoc)
	{
		fd->fd_heredoc = open(HEREDOC_NAME, O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (fd->fd_heredoc == -1) {
			fprintf(stderr, "[Error]: Redirection failed\n");
			return 0;
		}
		if (heredoc_func(fd->fd_heredoc, fdNames.fd_heredoc))
			return (0);
		close(fd->fd_heredoc);
		fd->fd_heredoc = open(HEREDOC_NAME, O_CREAT | O_RDONLY, 0777);
		if (fd->fd_heredoc == -1) {
			fprintf(stderr, "[Error]: Redirection failed\n");
			return 0;
		}
		return (fd->fd_heredoc);
	}
	return (1);
}

int	redirect(t_fds fd)
{
	if (fd.fd_in != -2)
	{
		if (dup2(fd.fd_in, 0) == -1)
			return (0);
	}
	if (fd.fd_out != -2)
	{
		if (dup2(fd.fd_out, 1) == -1)
			return (0);
	}
	if (fd.fd_append != -2)
	{
		if (dup2(fd.fd_append, 1) == -1)
			return (0);
	}
	if (fd.fd_heredoc != -2)
	{
		if (dup2(fd.fd_heredoc, 0) == -1)
			return (0);
	}
	return (1);
}

int parse_redirections(t_Redirection *redir_lst)
{
	t_fds		fd;
	t_fdNames	fdNames;
	int			ret;

	init_fd(&fd);
	init_fdNames(&fdNames);
	determine_redirections(&fdNames, redir_lst);
	if (!(ret = act_redirections(&fd, fdNames)))
		return (0);
	if (!redirect(fd))
		return (0);
	return (ret);
}

int	get_type(Token *tok_lst)
{
	int	type;

	type = 0;
	if (tok_lst->type == TOK_REDIRECT_IN)
	{
		type = REDIR_IN;
	}
	else if (tok_lst->type == TOK_REDIRECT_OUT)
	{
		type = REDIR_OUT;
	}
	else if (tok_lst->type == TOK_REDIRECT_APPEND)
		type = REDIR_APPEND;
	else if (tok_lst->type == TOK_REDIRECT_HEREDOC)
		type = REDIR_HEREDOC;
	return (type);
}

t_Redirection	*convert_tokens(Token *tok_lst)
{
	t_Redirection	*result;
	int			type;
	char		*str;

	result = NULL;
	while (tok_lst)
	{
		type = get_type(tok_lst);
		tok_lst = tok_lst->next;
		str = tok_lst->word;
		redir_add_back(&result, redir_create(str, type));
		tok_lst = tok_lst->next;
	}
	return (result);
}


int	parse_tok_redir(Token *token_lst, int stdin_fd)
{
	t_Redirection	*redir_lst;
	int				return_val;

	if (token_lst == NULL)
		return (1);
	g_stdin = stdin_fd;
	redir_lst = convert_tokens(token_lst);
	if (!redir_lst)
		return (0);
	return_val = parse_redirections(redir_lst);
	redir_free(redir_lst);
	return (return_val);
}