/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knishiok <knishiok@student.42.jp>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:14:15 by knishiok          #+#    #+#             */
/*   Updated: 2023/12/01 21:14:10 by knishiok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

# include "libft.h"
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

volatile sig_atomic_t	g_signal;

void	idle_handler(int signum);
void	heredoc_handler(int signum);
void	exec_handler(int signum);
void	handler_ignore(int signum);

void	set_idle_handler(void);
void	set_exec_handler(bool wait_child);
void	set_exec_child_handler(void);
void	set_heredoc_handler(void);
void	set_heredoc_child_handler(void);
#endif