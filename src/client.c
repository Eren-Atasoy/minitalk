/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/12/12 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack = 1;
}

static int	setup_client(int *server_pid, char *pid_str)
{
	struct sigaction	sa;

	*server_pid = ft_atoi(pid_str);
	if (!is_valid_pid(pid_str) || *server_pid <= 0)
	{
		ft_putstr_fd("Error: Invalid PID\n", 2);
		return (1);
	}
	if (kill(*server_pid, 0) == -1)
	{
		ft_putstr_fd("Error: Server not found\n", 2);
		return (1);
	}
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd("Error: sigaction failed\n", 2);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	pid;

	if (argc != 3)
	{
		ft_putstr_fd("Usage: ./client [server_pid] [message]\n", 1);
		return (1);
	}
	if (setup_client(&pid, argv[1]) != 0)
		return (1);
	send_string(pid, argv[2]);
	return (0);
}
