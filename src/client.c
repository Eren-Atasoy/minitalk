/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eratasoy <eratasoy@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 16:38:06 by eratasoy          #+#    #+#             */
/*   Updated: 2025/12/14 16:38:06 by eratasoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_received = 0;

static void	confirm_signal(int signum)
{
	(void)signum;
	g_received = 1;
}

static void	transmit_char(pid_t server_pid, unsigned char character)
{
	int	bit_pos;

	bit_pos = 7;
	while (bit_pos >= 0)
	{
		g_received = 0;
		if ((character >> bit_pos) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		while (!g_received)
			pause();
		bit_pos--;
	}
}

static	int	pid_checker(char *pid_str)
{
	int	count;
	int	pid;

	count = ft_strlen(pid_str);
	if (count > 7)
	{
		write(2, "Error: PID too long\n", 20);
		exit(1);
	}
	pid = ft_atoi(pid_str);
	if (pid <= 0 || pid >= 4194304)
	{
		write(2, "Error: Invalid PID\n", 19);
		exit(1);
	}
	return (pid);
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	int					idx;
	struct sigaction	act;

	if (argc != 3)
		return (ft_putstr_fd("Usage: ./client <pid> <message>\n", 2), 1);
	server_pid = pid_checker(argv[1]);
	if (server_pid <= 0 || kill(server_pid, 0) == -1)
		return (ft_putstr_fd("Error: Invalid PID\n", 2), 1);
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = confirm_signal;
	sigaction(SIGUSR1, &act, NULL);
	idx = 0;
	while (argv[2][idx])
	{
		transmit_char(server_pid, (unsigned char)argv[2][idx]);
		idx++;
	}
	transmit_char(server_pid, 0);
	return (0);
}
