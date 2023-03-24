/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:59:01 by lmiehler          #+#    #+#             */
/*   Updated: 2023/03/17 15:48:05 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "cmds.h"
#include "executioner.h"
#include "utils.h"
#include "signals.h"
#include "lexer.h"

void init_meta(t_meta *meta, char **envp)
{
	meta->envp = dp_cpy(envp);//!Should free this at exit
	meta->exit_status = 0;
	meta->cmd = NULL;
	meta->cmd_args = NULL;
	meta->infile.file = NULL;
	meta->outfile.file = NULL;
	meta->infile.append = 0;
	meta->outfile.append = 0;
}

void	print_block(t_code_block *b)
{
	if (b->symbol == 1)
	{		
		ft_printf("=====SYMBOL=====\n");
		ft_printf("Symbol = %s\n", b->words[0]);
		ft_printf("======END=======\n\n\n");
		return ;
	}
	ft_printf("=====COMMAND=====\n");
	ft_printf("Command = %s\n", b->words[0]);
	int i = 0;
	while (b->words[++i])
	{
		ft_printf("Arg[%i] = %s\n", i, b->words[i]);
	}
	ft_printf("=======END=======\n\n\n");
	return ;
}

void	print_io_config(t_meta *meta)
{
	ft_printf("----IO Config----\n");
	ft_printf("Infile : ");
	if (meta->infile.file == NULL)
		ft_printf("STDIN\n");
	else
	{
		if (meta->infile.append)
			ft_printf("<< ");
		else
			ft_printf("< ");
		ft_printf("%s\n", meta->infile.file);
	}
	ft_printf("Outfile: ");
	if (meta->outfile.file == NULL)
		ft_printf("STDOUT\n");
	else
	{
		if (meta->outfile.append)
			ft_printf(">> ");
		else
			ft_printf("> ");
		ft_printf("%s\n", meta->outfile.file);
	}
	ft_printf("\n\n");
}

void	print_tokens(t_token *tokens)
{
	t_token *cur;

	cur = tokens;
	while (cur)
	{
		ft_printf("\n===Token===\n");
		ft_printf("Type: {%c}\n", cur->type);
		ft_printf("Str: {%s}\n", cur->str);
		cur = cur->next;
	}
}

void	print_blocks(t_code_block *blocks)
{
	t_code_block	*cur;

	cur = blocks;
	while (cur)
	{
		print_block(cur);
		cur = cur->next;
	}
}

void	cleanup(t_meta *meta)
{
	token_clear(&meta->tokens);
	block_clear(&meta->blocks);
}

//! all built in commands take wrong arguments because of execve
int	main(int argc, char **argv, char **envp)
{
	t_token *tokens;
	t_token *tokens_start;
	t_code_block	*blocks;
	t_meta	meta;
	char	*line;

	init_meta(&meta, envp);
	init_signals();
	ft_printf("Hi Mom\n");
	while (1)
	{
		line = readline("\033[0;31m[Gigashell]\033[0m% ");
		if (line == NULL) // ctrl-D handling
			exit(0);
		if (is_unclosed_quote(line))
			ft_printf("ERROR: unclosed quotes\n");
		if (!ft_strncmp(line, "exit", 5))
			exit(0);
		add_history(line);
		meta.tokens = lexer(line, envp);
		print_tokens(meta.tokens);
		meta.blocks = parser(&meta, meta.tokens);
		print_blocks(meta.blocks);
		print_io_config(&meta);
		executioner(&meta);
		cleanup(&meta);
		tokens = lexer(line, envp);
		//print_tokens(tokens);
		if (validate(tokens))
		{
			blocks = parser(&meta, tokens);
			executioner(blocks, &meta);
			block_clear(&blocks);
		}
		token_clear(&tokens);
	}
	return (0);
}
