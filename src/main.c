/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:23:11 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/24 17:13:03 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include "./signals/signals.h"
#include "expander.h"
#include "interpreter.h"

extern PidList	*g_pid_list;
char			**g_envp;


int	is_unclosed_quote(char *str)
{
	int		i;
	char	openq;

	i = 0;
	openq = 0;
	while (str[i])
	{
		if (openq == 0)
		{
			openq = is_quote(str[i]);
		}
		else
		{
			if (openq == is_quote(str[i]))
				openq = 0;
		}
		i++;
	}
	return (openq);
}


int	evaluate_line(char *line)
{
	AstNode	*ast;

	if (is_unclosed_quote(line))
	{
		printf("[Error]: Command line has unclosed quote\n");
		return (1);
	}
	ast = parser(line);
	g_ast = ast;
	if (ast == NULL)
		return (1);
	interpreter(ast);
	free_ast(ast);
	return (1);
}

int	read_loop( void )
{
	char	*line;

	while (1)
	{
		line = readline("DEATH....>");
		if (line == NULL)
		{
			return (1);
		}
		if (line[0] != '\0')
		{
			add_history(line);
			if (!evaluate_line(line))
				return (1);
			pidList_clear(&g_pid_list);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc || argv)
		;
	setup(envp);
	read_loop();
	cleanup();
	return (0);
}

