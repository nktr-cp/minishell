/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: misargsy <misargsy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:45:48 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/26 21:19:07 by misargsy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execute.h"
#include "env.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>

static void	initialize(t_exec *config, char **envp)
{
	rl_instream = stdin;
	rl_outstream = stdout;
	config->env = env_init(envp);
	config->exit_code = EXIT_OK;
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_exec		config;
	t_state		data;
	t_ast_node	*node;

	(void)argc;
	(void)argv;
	initialize(&config, envp);
	while (true)
	{
		line = readline("\x1b[31mMINISHELL>>\x1b[0m ");
		if (line == NULL)
			break ;
		node = parse(&data, line);
		if (node == NULL)
			continue ;
		execute(node, &config);
		wait(NULL);
		destroy_ast_node(node);
		add_history(line);
		free(line);
	}
	exit(EXIT_SUCCESS);
}
