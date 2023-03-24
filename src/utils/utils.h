/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 18:17:56 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/22 16:46:32 by lmiehler         ###   ########.fr       */
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
int		dp_free(char **str);

char	is_quote(char c);

int	is_unclosed_quote(char *str);

#endif