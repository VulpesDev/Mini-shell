/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:41:11 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/14 12:43:23 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include "libft.h"
#include "utils.h"
#include "cmds.h"
#define PWD_SIZE 10000

//TODO too many arguments error if an argument is passed
int	gs_pwd_error(const char *message)
{
	//!What was the printf function Luca mentioned?
	ft_printf("pwd: %s\n", message);
	return (1);
}

int	gs_pwd(t_meta *meta)
{
	char	*buf;

	if (*meta->cmd_args)
		return gs_pwd_error("too many arguments");
	buf = xmalloc(PWD_SIZE * sizeof(char));
	getcwd(buf, PWD_SIZE);
	ft_printf("%s\n", buf);
	return (0);
}