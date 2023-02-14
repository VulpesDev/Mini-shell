/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:35:17 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/14 13:45:40 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<unistd.h>
#include "libft.h"
#include "cmds.h"

/////TODO cd without arguments goes to user home
/////TODO cd with '~' as an argument goes to user home
/////TODO if directory does not exist display 'cd: no such file or directory: {arg}'
int	gs_chdir_protect(char	*path)
{
	if (chdir(path))
	{
		ft_fprintf(2, "cd: no such file or directory: %s\n", path);
		return (1);
	}
	return (0);
}

int	gs_cd(t_meta *meta)
{
	if (meta->cmd_args[1])
	{
		ft_fprintf(2, "cd: too many arguments\n");
		return (1);
	}
	else if (!meta->cmd_args[0])
		return (gs_chdir_protect(getenv("HOME")));
	else if (!ft_strncmp("~", meta->cmd_args[0], 2))
		return (gs_chdir_protect(getenv("HOME")));
	else
		return (gs_chdir_protect(meta->cmd_args[0]));
}