/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manujime <manujime@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:02:07 by albgonza          #+#    #+#             */
/*   Updated: 2023/06/13 18:55:40 by manujime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	*g_ptr_active;

void	signal_handler(int signal)
{
	(void) signal;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	if (ft_active_getter() == 0)
		rl_redisplay();
}

void	signal_setter(void)
{
	struct sigaction	sa_ignore;

	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = 0;
	sigaction(SIGQUIT, &sa_ignore, NULL);
	signal(SIGINT, signal_handler);
}

void	ft_active_setter(int i)
{
	static int	g_active;

	g_active = i;
	g_ptr_active = &g_active;
}

int	ft_active_getter(void)
{
	int	g_active;

	g_active = *g_ptr_active;
	return (g_active);
}
