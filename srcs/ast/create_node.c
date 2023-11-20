/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:23:24 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/20 18:02:28 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"


bool	add_command(t_ast_node *node, char *command)
{
	t_list	*val_lst;

	if (node == NULL || command == NULL)
		return (false);
	if (node->command == NULL)
		node->command = command;
	val_lst = ft_lstnew(command);
	if (val_lst == NULL)
		return (false);
	ft_lstadd_back(&(node->command), val_lst);
	return (true);
}

bool	add_redirect(t_ast_node *node, t_redir *redir)
{
	t_list	*val_lst;

	if (node == NULL || redir == NULL)
		return (false);
	if (node->redir == NULL)
		node->redir = redir;
	val_lst = ft_lstnew(redir);
	if (val_lst == NULL)
		return (false);
	ft_lstadd_back(&(node->redir), val_lst);
	return (true);
}

t_ast_node	*new_ast_node(t_ast_type type,
	t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*res;

	res = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
	if (res == NULL)
	{
		destroy_node(left);
		return (NULL);
	}
	res->type = type;
	res->left = left;
	res->right = right;
	return (res);
}

t_redir	*new_redir(t_redir_type type, char *filename)
{
	t_redir	*res;

	res = (t_redir *)ft_calloc(1, sizeof(t_redir));
	if (res == NULL)
		return (NULL);
	res->type = type;
	res->filename = filename;
	return (res);
}
