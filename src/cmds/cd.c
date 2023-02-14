/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:35:17 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/14 12:48:05 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<unistd.h>
#include "libft.h"
#include "cmds.h"

/////TODO cd without arguments goes to user home
/////TODO cd with '~' as an argument goes to user home
//TODO if directory does not exist display 'cd: no such file or directory: {arg}'
int	gs_cd(t_meta *meta)
{
	if (!meta->cmd_args[0])
		chdir(getenv("HOME"));
	else if (!ft_strncmp("~", meta->cmd_args[0], 2))
		chdir(getenv("HOME"));
	else
		chdir(meta->cmd_args[0]);
	return(0);
}