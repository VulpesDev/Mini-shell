/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:41:11 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/14 11:35:06 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include "libft.h"
#define PWD_SIZE 10000

void	gs_pwd(void)
{
	char	*buf;

	buf = xmalloc(PWD_SIZE * sizeof(char));
	getcwd(buf, PWD_SIZE);
	ft_printf("%s\n", buf);
}