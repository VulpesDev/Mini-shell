/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvasilev <tvasilev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 14:43:24 by tvasilev          #+#    #+#             */
/*   Updated: 2023/05/17 13:58:01 by tvasilev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interpreter.h"
#include "lexer.h"
#include "redirections.h"

Stack	*pipe_stack;
int		stdout_fd;
int		stdin_fd;
int		recent_exit_status;
PidList	*g_pid_list;

int	traceback_pipes(Stack *pipe_stack)
{
	Stack	*cur;
	int		i;

	cur = pipe_stack;
	i = 0;
	while (cur)
	{
		if (cur->written_to == true) {
			return (cur->pd[0]);
		}
		i++;
		cur = cur->next;
	}
	return (-1);
}

int top_null(AstNode *node, int *heredoc_pid)
{
	dup2(stdin_fd, 0);
	dup2(stdout_fd, 1);
	if (!(*heredoc_pid =
			parse_tok_redir(node->command_node.redirections, stdin_fd)))
		return (0);
	return (1);
}

void conf_u(Stack *top)
{
	int traceback_pd = traceback_pipes(pipe_stack);
	if (traceback_pd != -1)
		dup2(traceback_pd, 0);
	if (dup2(top->pd[1] ,1) == -1)
		fprintf(stderr, "dup2 failed\n");
}

void conf_l(Stack *top)
{
	if (dup2(top->pd[0] ,0) == -1)
		fprintf(stderr, "dup2 failed\n");
	if (top->next != NULL && top->next->written_to == false)
	{
		if (dup2(top->next->pd[1], 1) == -1)
			fprintf(stderr, "dup2 failed\n");
	}
	else
	{
		if (dup2(stdout_fd, 1) == -1)
			fprintf(stderr, "dup2 failed\n");
	}	
}

int	configure_io(AstNode *node, int *heredoc_pid)
{
	Stack	*top;

	top = stack_top(&pipe_stack);
	if (top == NULL)
		return top_null(node, heredoc_pid);
	if (top->written_to == false)
		conf_u(top);
	else
		conf_l(top);
	if(!(*heredoc_pid =
			parse_tok_redir(node->command_node.redirections, stdin_fd)))
		return (0);
	return (1);
}

void	unlink_heredoc(Token *redir_lst, int heredoc_pid)
{
	while (redir_lst)
	{
		if (redir_lst->type == TOK_REDIRECT_HEREDOC)
		{
			redir_lst = redir_lst->next;
			unlink(HEREDOC_NAME);
			close(heredoc_pid);
		}
		redir_lst = redir_lst->next;
	}
}

int interpret_command_node(AstNode *node)
{
	int	heredoc_pid;
	int status, is_last;

	if (!configure_io(node, &heredoc_pid))
		return 1;
	if (!pipe_stack || (pipe_stack->next == NULL && pipe_stack->written_to == true)
		|| (pipe_stack->next && pipe_stack->written_to == true && pipe_stack->next->written_to == true)) 
		is_last = 1;
	else
		is_last = 0;
	status = execute_command(node->command_node.command, is_last);
	unlink_heredoc(node->command_node.redirections, heredoc_pid);
	return status;
}

int	interpret_pipeline_node(AstNode *node)
{
	int	status;

	stack_push(&pipe_stack);
	interpret(node->pipeline_node.left);
	pipe_stack->written_to = true;
	close(pipe_stack->pd[1]);
	status = interpret(node->pipeline_node.right);
	close(pipe_stack->pd[0]);
	stack_pop(&pipe_stack);
	return (status);
}

int	interpret_conditional_node(AstNode *node)
{
	if (node->conditional_node.type == COND_AND)
	{
		return (interpret(node->conditional_node.left)
			&& interpret(node->conditional_node.right));
	}
	else
	{
		return (interpret(node->conditional_node.left)
			|| interpret(node->conditional_node.right));
	}
}

int	interpret(AstNode *node)
{
	switch(node->type)
	{
		case AST_CONDITIONAL_NODE:
			return interpret_conditional_node(node);
		case AST_PIPELINE_NODE:
			return interpret_pipeline_node(node);
		case AST_COMMAND_NODE:
			return interpret_command_node(node);
		default:
			return 0;
	}
}

int	interpreter(AstNode *ast)
{
	g_pid_list = NULL;
	stdout_fd = dup(1);
	stdin_fd = dup(0);
	interpret(ast);
	dup2(stdin_fd, 0);
	dup2(stdout_fd, 1);
	return (1);
}