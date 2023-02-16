/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmiehler <lmiehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:04:58 by lmiehler          #+#    #+#             */
/*   Updated: 2023/02/16 20:45:50 by lmiehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

/**
 * Takes a string and expands $ expressions to their corresponding
 * enviroment variable
 * ! Questionable malloc practice. Will fail for very large input 
 * ! (nobody needs to know)
 * @param str String to expand
 * @param envp Enviroment used to look up expansions
 * @return Expanded String
*/
char	*expand_variables(char *str, char **envp);

/**
 * Takes a pattern containing wildcards ('*') and finds all the matching
 * files and directories in the current working directory
 * ! Questionable malloc practice. Will fail for very large input
 * ! (nobody needs to know)
 * @param pattern Pattern to match to
 * @return String of strings which holds all strings that matched the pattern
*/
char	**expand_wildcards(char *pattern);

#endif