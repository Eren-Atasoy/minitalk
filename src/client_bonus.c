/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/12/12 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static volatile sig_atomic_t	g_received = 0;

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

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	int					idx;
	struct sigaction	act;

	if (argc != 3)
		return (ft_putstr_fd("Usage: ./client <pid> <msg>\n", 2), 1);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0 || kill(server_pid, 0) == -1)
		return (ft_putstr_fd("Error: Invalid PID\n", 2), 1);
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	act.sa_handler = confirm_signal;
	sigaction(SIGUSR1, &act, NULL);
	idx = 0;
	while (argv[2][idx])
	{
		transmit_char(server_pid, (unsigned char)argv[2][idx]);
		idx++;
	}
	transmit_char(server_pid, 0);
	ft_putstr_fd("Message sent!\n", 1);
	return (0);
}
