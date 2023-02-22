/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:59:01 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/22 12:42:10 by tvasilev         ###   ########.fr       */
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
		line = readline("[Gigashell]% ");
		add_history(line);
		tokens = lexer(line);
		blocks = parser(&meta, tokens);
		blocks_start = blocks;
		while (blocks)
		{
			int i = -1;
			
			ft_printf("code block\n---------\n");
			ft_printf("symbol:  %i\n", blocks->symbol);
			while (blocks->words[++i])
				ft_printf("words:  %i-%s\n", i, blocks->words[i]);
			blocks = blocks->next;
			ft_printf("\n---------\n\n");
		}
		executioner(&meta);
		token_clear(&tokens);
		block_clear(&blocks_start);
	}
	return (0);
}
