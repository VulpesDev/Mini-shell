/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:59:01 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/23 23:23:53 by lmiehler         ###   ########.fr       */
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
		ft_printf("Type: %c\n", cur->type);
		ft_printf("Str: %s\n", cur->str);
		cur = cur->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_token *tokens;
	t_token *tokens_start;
	t_code_block	*blocks;
	t_code_block	*blocks_start;
	t_meta	meta;
	char	*line;

	init_meta(&meta, envp);
	ft_printf("Hi Mom\n");
	while (1)
	{
		line = readline("\033[0;31m[Gigashell]\033[0m% ");
		add_history(line);
		tokens = lexer(line, envp);
		print_tokens(tokens);
		blocks = parser(&meta, tokens);
		blocks_start = blocks;
		ft_printf("\n\n");
		while (blocks)
		{
			print_block(blocks);
			// int i = -1;
			
			// ft_printf("code block\n---------\n");
			// ft_printf("symbol:  %i\n", blocks->symbol);
			// while (blocks->words[++i])
			// 	ft_printf("words:  %i-%s\n", i, blocks->words[i]);
			blocks = blocks->next;
		}
		print_io_config(&meta);
		ft_printf("infile: %s\nappend: %d\noutfile: %s\nappend: %d\n", meta.infile.file,
			meta.infile.append, meta.outfile.file, meta.outfile.append);
		executioner(&meta);
		token_clear(&tokens);
		block_clear(&blocks_start);
	}
	return (0);
}
