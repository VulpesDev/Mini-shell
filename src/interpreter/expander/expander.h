/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:04:58 by lmiehler          #+#    #+#             */
/*   Updated: 2023/05/07 13:48:32 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

/**
 * Takes a string and expands $ expressions to their corresponding
 * enviroment variable
 * Leaks: I think it's leak free. Havent done extensive testing
 * @param str String to expand
 * @param envp Enviroment used to look up expansions
 * @return Expanded String
*/
char	*expand_variables(char *str, char **envp);

/**
 * Takes a pattern containing wildcards ('*') and finds all the matching
 * files and directories in the current working directory
 * Leaks: Is leak free. Still have to free return variable
 * @param pattern Pattern to match to
 * @return String of strings which holds all strings that matched the pattern
*/
Token	*expand_wildcards(char *pattern);
char	is_quote(char c);
char	*gs_getenv(char *str, char **envp);
int		contains_wildcard(char *str);
Token	*expander(Token *commands);
char	*remove_quotes(char *str);

#endif