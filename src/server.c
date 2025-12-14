/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eratasoy <eratasoy@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:37:29 by eratasoy          #+#    #+#             */
/*   Updated: 2025/12/14 18:10:04 by eratasoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	receive_bit(int signum, siginfo_t *data, void *ucontext)
{
	static unsigned char	byte;
	static int				bit_pos;

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
	if (data->si_pid != 0)
		kill(data->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	act;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = receive_bit;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
	return (0);
}
