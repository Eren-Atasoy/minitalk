/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/12/12 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	current = 0;
	static int				bit_index = 0;

	(void)context;
	current <<= 1;
	if (sig == SIGUSR2)
		current |= 1;
	bit_index++;
	if (bit_index == 8)
	{
		if (current == '\0')
		{
			write(1, "\n", 1);
			if (info && info->si_pid > 0)
				kill(info->si_pid, SIGUSR2);
		}
		else
			write(1, &current, 1);
		current = 0;
		bit_index = 0;
	}
	if (info && info->si_pid > 0)
		kill(info->si_pid, SIGUSR1);
}

static void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error: sigaction failed\n", 2);
		exit(1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error: sigaction failed\n", 2);
		exit(1);
	}
}

int	main(void)
{
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	setup_signals();
	while (1)
		pause();
	return (0);
}
