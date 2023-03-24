/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:20:22 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/26 16:22:48 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include "minishell.h"

void	del_here_doc(void)
{
	if (unlink(DOC_NAME) == -1)
		ft_fprintf(2, "Error unlink\n");
}

void	create_here_doc(char *limiter)
{
	int		doc_fd;
	char	*str;

	doc_fd = open(DOC_NAME, O_CREAT | O_WRONLY, 0777);
	if (doc_fd == -1)
		ft_fprintf(2, "Error open\n");
	str = get_next_line(0);
	while (ft_strncmp(str, limiter, ft_strlen(limiter)))
	{
		ft_fprintf(doc_fd, "%s", str);
		free(str);
		str = get_next_line(0);
	}
	free(str);
	close(doc_fd);
}