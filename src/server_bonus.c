/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eratasoy <eratasoy@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:37:48 by eratasoy          #+#    #+#             */
/*   Updated: 2025/12/14 16:37:48 by eratasoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	receive_bit(int signum, siginfo_t *data, void *ucontext)
{
	static unsigned char	byte = 0;
	static int				bit_pos = 0;

	(void)ucontext;
	byte <<= 1;
	if (signum == SIGUSR1)
		byte |= 1;
	bit_pos++;
	if (bit_pos == 8)
	{
		if (byte == 0)
			write(1, "\n", 1);
		else
			write(1, &byte, 1);
		byte = 0;
		bit_pos = 0;
	}
	if (data && data->si_pid != 0)
		kill(data->si_pid, SIGUSR1);
}

static void	init_signals(void)
{
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = receive_bit;
	if (sigaction(SIGUSR1, &act, NULL) == -1)
	{
		ft_putstr_fd("Error: sigaction failed\n", 2);
		exit(1);
	}
	if (sigaction(SIGUSR2, &act, NULL) == -1)
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
	init_signals();
	while (1)
		pause();
	return (0);
}
