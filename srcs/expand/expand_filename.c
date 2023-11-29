/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 21:01:19 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/29 18:29:50 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

static t_list	*get_filenames(void)
{
	t_list			*res;
	t_list			*new;
	char			*filename;
	DIR				*dir;
	struct dirent	*entry;

	res = NULL;
	dir = opendir("./");
	if (dir == NULL)
		return (operation_failed("Cannot open the current directory"), NULL);
	while (1)
	{
		entry = readdir(dir);
		if (entry == NULL)
			break ;
		filename = ft_strdup(entry->d_name);
		if (filename == NULL)
			return (ft_lstclear(&res, free), operation_failed("malloc"), NULL);
		new = ft_lstnew(filename);
		if (new == NULL)
			return (ft_lstclear(&res, free), operation_failed("malloc"), NULL);
		ft_lstadd_back(&res, new);
	}
	closedir(dir);
	return (res);
}

static bool	merge_list(char *filename, bool flg, t_list **res)
{
	t_list	*new;
	char	*content;

	if (flg)
		return (ft_lstclear(res, free), operation_failed("malloc"), false);
	content = ft_strdup(filename);
	if (content == NULL)
		return (ft_lstclear(res, free), operation_failed("malloc"), false);
	new = ft_lstnew(content);
	if (new == NULL)
		return (ft_lstclear(res, free), operation_failed("malloc"), false);
	ft_lstadd_back(res, new);
	return (true);
}

static t_list	*expand_filename(char *pattern)
{
	t_list	*head;
	t_list	*dir_filenames;
	t_list	*res;
	bool	malloc_flg;

	res = NULL;
	dir_filenames = get_filenames();
	if (dir_filenames == NULL)
		return (NULL);
	head = dir_filenames;
	malloc_flg = false;
	while (dir_filenames)
	{
		if (matched(dir_filenames->content, pattern, &malloc_flg))
		{
			if (!merge_list(dir_filenames->content, malloc_flg, &res))
				return (NULL);
		}
		dir_filenames = dir_filenames->next;
	}
	ft_lstclear(&head, free);
	return (res);
}

static t_list	*duplicate_filename(char *filename)
{
	t_list	*res;
	char	*dup_filename;

	dup_filename = ft_strdup(filename);
	if (dup_filename == NULL)
		return (NULL);
	res = ft_lstnew(dup_filename);
	if (res == NULL)
	{
		free(dup_filename);
		return (NULL);
	}
	return (res);
}

t_list	*expand_wildcard(t_list **input)
{
	t_list	*res;
	t_list	*new;
	t_list	*head;

	res = NULL;
	head = *input;
	while (*input)
	{
		if (ft_strchr((*input)->content, '*') != NULL)
			new = expand_filename((*input)->content);
		else
		{
			new = duplicate_filename((*input)->content);
			if (new == NULL)
				return (ft_lstclear(&res, free),
					ft_lstclear(&head, free), operation_failed("malloc"), NULL);
		}
		ft_lstadd_back(&res, new);
		*input = (*input)->next;
	}
	ft_lstclear(&head, free);
	return (res);
}
