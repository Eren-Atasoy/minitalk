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

volatile sig_atomic_t	g_ack = 0;

static void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
	else if (sig == SIGUSR2)
	{
		ft_putstr_fd("Message received by server!\n", 1);
		exit(0);
	}
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
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	return (0);
}

static void	send_char_bonus(int pid, unsigned char c)
{
	int	bit;
	int	sig;

	bit = 7;
	while (bit >= 0)
	{
		g_ack = 0;
		if ((c >> bit) & 1)
			sig = SIGUSR2;
		else
			sig = SIGUSR1;
		if (kill(pid, sig) == -1)
		{
			ft_putstr_fd("Error: Failed to send signal\n", 2);
			exit(1);
		}
		while (!g_ack)
			pause();
		bit--;
	}
}

static void	send_string_bonus(int pid, char *str)
{
	while (*str)
	{
		send_char_bonus(pid, (unsigned char)*str);
		str++;
	}
	send_char_bonus(pid, '\0');
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
	send_string_bonus(pid, argv[2]);
	return (0);
}

