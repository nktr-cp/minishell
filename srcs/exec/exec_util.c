/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:15:01 by misargsy          #+#    #+#             */
/*   Updated: 2023/11/29 19:01:03 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	exec_non_bi_in_child_process(const char *command, t_list *args,
		t_exec *config)
{
	char	**argv;
	char	**envp;

	set_exec_child_handler();
	if (!expand_command_list(&args, config->env))
	{
		operation_failed("malloc");
		exit(EXIT_KO);
	}
	argv = t_list_to_array(command, args);
	envp = env_to_array(config->env);
	if ((argv == NULL) || (envp == NULL))
	{
		free2darr(argv);
		free2darr(envp);
		operation_failed("malloc");
		exit(EXIT_KO);
	}
	ft_execvp(command, argv, envp);
	free2darr(argv);
	free2darr(envp);
	exit(execvp_failed(command));
}

t_exit_code	single_fork_destructor(pid_t pid, t_exec *config)
{
	int	status;

	if (config->fork_count != 0)
	{
		config->fork_count = 0;
		if (waitpid(pid, &status, 0) < 0)
			waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			return (WTERMSIG(status) + 128);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (EXIT_KO);
}

t_exit_code	pipeline_forks_destructor(t_exec *config)
{
	int	status;

	while (config->fork_count > 0)
	{
		if (wait(&status) < 0)
			return (operation_failed("wait"), EXIT_KO);
		if (WIFEXITED(status))
			config->exit_code = WEXITSTATUS(status);
		status = 0;
		config->fork_count--;
	}
	config->fork_count = 0;
	return (config->exit_code);
}
