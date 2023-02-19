/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:59:01 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/19 15:19:45 by tvasilev         ###   ########.fr       */
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
	t_meta	meta;
	char	*line;

	init_meta(&meta, envp);
	ft_printf("Hi Mom\n");
	while (1)
	{
		line = readline("[Gigashell]% ");
		add_history(line);
		parser(&meta, line);
		tokens = lexer(line);
		while (tokens)
		{
			ft_printf("%s:", tokens->str);
			if (tokens->type == 'w')
				ft_printf("%s\n", "word");
			else if (tokens->type == 's')
				ft_printf("%s\n", "symbol");
			tokens = tokens->next;
		}
		executioner(&meta);
	}
	return (0);
}
