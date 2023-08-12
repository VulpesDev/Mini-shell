/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:47:33 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/24 17:12:50 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERPRETER_H
# define INTERPRETER_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include "minishell.h"

extern int stdout_fd;
extern int stdin_fd;
extern AstNode *g_ast;
extern int recent_exit_status;

typedef struct Stack
{
	int				pd[2];
	bool			written_to;
	struct Stack	*next;
}					Stack;

extern Stack	*pipe_stack;

typedef struct PidList
{
	int				pid;
	struct PidList	*next;
}PidList;

PidList	*pidList_create(int pid);

PidList	*pidList_last(PidList *lst);

void	pidList_add(PidList **lst, PidList *new_elem);

void	pidList_print(PidList *lst);

void	pidList_clear(PidList **cur);

void	cleanup_processes(PidList *cur);

// -----Basic Stack Functions-----

Stack	*stack_push(Stack **stack);
Stack	*stack_pop(Stack **stack);
Stack	*stack_top(Stack **stack);

int		interpret(AstNode *node);
int		interpreter(AstNode *node);

int		execute_command(Token *command, bool is_last);

#endif