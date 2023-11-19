/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:22:28 by knishiok          #+#    #+#             */
/*   Updated: 2023/11/19 16:15:26 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*create_token(char *word, int type)
{
	t_token	*new_token;

	if (word == NULL)
		return (NULL);
	new_token = ft_calloc(1, sizeof(t_token));
	new_token->word = word;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

static t_token	*parse_metacharacters(char **line)
{
	const char	*ops[] = {"&&", "||", "|", "<<", ">>", "<", ">"};
	const int	types[] = {TK_AND, TK_OR, TK_PIPE, TK_IN,
		TK_OUT, TK_HEREDOC, TK_APPEND};
	size_t		i;
	char		*word;

	i = 0;
	while (i < sizeof(ops) / sizeof(*ops))
	{
		if (corresponds(*line, ops[i]))
			break ;
		i++;
	}
	*line += ft_strlen(ops[i]);
	word = ft_strdup(ops[i]);
	return (create_token(word, types[i]));
}

static t_token	*parse_word(t_data *data, char **line)
{
	char	*head;
	char	*tmp;
	char	quote;

	head = *line;
	tmp = *line;
	while (*tmp && !is_space(*tmp) && !is_metacharacter(*tmp))
	{
		if (*tmp == '\'' || *tmp == '\"')
		{
			quote = *tmp++;
			while (*tmp != '\0' && *tmp != quote)
				tmp++;
			if (!*tmp)
			{
				set_syntax_error(data);
				return (NULL);
			}
		}
		tmp++;
	}
	*line = tmp;
	return (create_token(ft_substr(head, 0, tmp - head), TK_WORD));
}

void	tokenize(t_data *data, char *line)
{
	t_token	head;
	t_token	*cur;

	cur = &head;
	while (*line)
	{
		skip_spaces(&line);
		if (is_metacharacter(*line))
		{
			cur->next = parse_metacharacters(&line);
			if (cur->next == NULL)
				return (set_allocation_error(data, head.next));
			cur->next->prev = cur;
			cur = cur->next;
		}
		else
		{
			cur->next = parse_word(data, &line);
			if (cur->next == NULL)
				return (set_allocation_error(data, head.next));
			cur->next->prev = cur;
			cur = cur->next;
		}
	}
	data->token = head.next;
}