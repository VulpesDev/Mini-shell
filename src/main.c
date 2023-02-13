/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:59:01 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/13 18:16:29 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "minishell.h"
#include "parser.h"
#include "cmds.h"
#include "executioner.h"

void init_meta(t_meta *meta, char **envp)
{
	meta->envp = envp;
	meta->exit_status = 0;
	meta->cmd = NULL;
	meta->cmd_args = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	t_meta meta;
	init_meta(&meta, envp);
	ft_printf("Hi Mom\n");
	char *line;
	while (1)
	{
		line = readline("[Gigashell]% ");
		add_history(line);
		parser(&meta, line);
		executioner(&meta);
	}
	return (0);
}
