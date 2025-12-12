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
	static int	bit_index = 0;
	static char	current_char = 0;

	(void)context;
	if (sig == SIGUSR2)
		current_char |= (1 << (7 - bit_index));
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == '\0')
		{
			ft_putchar('\n');
			kill(info->si_pid, SIGUSR1);
		}
		else
			ft_putchar(current_char);
		bit_index = 0;
		current_char = 0;
	}
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
		ft_putstr("Error: sigaction failed\n");
		exit(1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr("Error: sigaction failed\n");
		exit(1);
	}
}

int	main(void)
{
	ft_putstr("Server PID: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	setup_signals();
	while (1)
		pause();
	return (0);
}
