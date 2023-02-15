/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:05:15 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/15 16:23:14 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include "utils.h"

char *gs_getenv(char *str, char **envp)
{
	char	*valuestr;
	char	*env_var;
	int	i;

	valuestr = NULL;
	env_var = ft_strjoin(str, "=");
	malloc_check((void *)env_var);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(env_var, envp[i], ft_strlen(env_var)))
		{
			valuestr = ft_substr(envp[i], ft_strlen(env_var), ft_strlen(envp[i]));
			malloc_check((void *)valuestr);
			break ;
		}
	}
	free(env_var);
	return (valuestr);
}

char *evaluate_dollar(char *str, char **envp)
{
	char	*key;
	char	*expansion;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	if (str[i] == '$' && (str[i + 1] != '\0' || str[i + 1] == '$'))
		return (ft_strdup("$"));
	while (str[i + 1] && str[i + 1] != '$')
		i++;
	key = ft_substr(str, 1, i);
	malloc_check((void *)key);
	expansion = gs_getenv(key, envp);
	free(key);
	return (expansion);
}

char *expand_variables(const char *str, t_meta *meta)
{
	int		i;
	t_list	*lst;

	i = 0;
	while(str[i])
	{
		if (str[i] == '$')
		{
			ft_lstadd_back(&lst, ft_lstnew(evaluate_dollar(&str[i], meta->envp)));
		}
		i++;
	}
	
}

char **expand_wildcards()
{

}
