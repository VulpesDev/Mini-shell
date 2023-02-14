/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 11:35:17 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/14 12:06:25 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

//TODO cd without arguments goes to user home
//TODO cd with '~' as an argument goes to user home
//TODO if directory does not exist display 'cd: no such file or directory: {arg}'
int	gs_cd(const char *path)
{
	chdir(path);
	return (0);
}