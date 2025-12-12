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

#include "minitalk.h"

int	g_received = 0;

static void	handle_ack(int sig)
{
	(void)sig;
	g_received = 1;
	ft_putstr("Message received by server!\n");
}

static void	setup_ack_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_ack;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr("Error: sigaction failed\n");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_putstr("Usage: ./client [server_pid] [message]\n");
		return (1);
	}
	if (!is_valid_pid(argv[1]))
	{
		ft_putstr("Error: Invalid PID\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr("Error: Invalid PID\n");
		return (1);
	}
	setup_ack_handler();
	send_string(pid, argv[2]);
	while (!g_received)
		pause();
	return (0);
}
