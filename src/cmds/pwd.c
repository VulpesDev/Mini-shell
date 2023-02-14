/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 10:41:11 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/14 11:07:07 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include "libft.h"

//? should I use write here?
void	gs_pwd(void)
{
	char	buf[1000];

	getcwd(buf, 1000);
	ft_printf("%s\n", buf);
}