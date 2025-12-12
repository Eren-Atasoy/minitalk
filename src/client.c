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
	send_string(pid, argv[2]);
	return (0);
}
