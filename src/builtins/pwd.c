/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:26:56 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/01 14:27:24 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	gs_pwd_error(const char *message)
{
	ft_fprintf(2, "pwd: %s\n", message);
	return (1);
}

int	gs_pwd(char **cmd_args)
{
	char	*buf;

	if (*cmd_args)
		return (gs_pwd_error("too many arguments"));
	buf = xmalloc(PWD_SIZE * sizeof(char));
	getcwd(buf, PWD_SIZE);
	ft_printf("%s\n", buf);
	free(buf);
	return (0);
}
