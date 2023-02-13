/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 11:33:03 by tvasilev          #+#    #+#             */
/*   Updated: 2023/02/13 11:37:09 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void    print_strs(char *str[])
{
    int i;

    i = 0;
    while (str[i])
    {
        ft_printf("%s\n", str[i]);
        i++;
    }
}

int main(int argc, char *argv[], char *envp[])
{
    print_strs(envp);
    return (0);
}