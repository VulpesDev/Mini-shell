/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:17:56 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/15 16:06:47 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <unistd.h>

void	print_strs(char *str[]);

void	*xmalloc(size_t size);

int	size_dp(char **str);

char	**cpy_dp(char **str);

#endif