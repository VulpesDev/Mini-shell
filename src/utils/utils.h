/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:17:56 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/16 20:25:05 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <unistd.h>

void	print_strs(char *str[]);

void	*xmalloc(size_t size);

void	malloc_check(void *p);

char *gs_getenv(char *str, char **envp);

int ft_isspace(char c);

#endif