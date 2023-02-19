/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:33:03 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/16 19:42:44 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include "libft.h"

void	print_strs(char *str[])
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	while (1)
	{
		line = readline("[Minishell]% ");
		add_history(line);
		if (!ft_strncmp("clear", line, 6))
			rl_clear_history();
		ft_printf("Str={%s}\n", line);
	}
	return (0);
}
