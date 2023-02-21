/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:17:56 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/21 13:21:32 by tvasilev         ###   ########.fr       */
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

/*gets the length of a double pointer(dp) array*/
int	dp_size(char **str);

/*duplicates a double pointer and returns a pointer to
the duplicate*/
char	**dp_cpy(char **str);

/*frees a double pointer array*/
int	dp_free(char **str);

#endif