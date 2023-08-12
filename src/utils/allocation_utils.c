/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 13:23:15 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/11 18:19:25 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	malloc_fail_procedure( void )
{
	printf("Error: malloc failed: terminating program\n");
	exit(1);
}

void	*xmalloc(size_t size)
{
	void	*p;

	p = malloc(size);
	if (p == NULL)
		malloc_fail_procedure();
	return (p);
}
