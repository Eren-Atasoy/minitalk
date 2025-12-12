/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/12/12 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_bit(int pid, int bit)
{
	int	sig;

	if (bit == 0)
		sig = SIGUSR1;
	else
		sig = SIGUSR2;
	if (kill(pid, sig) == -1)
	{
		ft_putstr("Error: Failed to send signal\n");
		exit(1);
	}
	usleep(100);
}

void	send_char(int pid, char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		send_bit(pid, (c >> bit) & 1);
		bit--;
	}
}

void	send_string(int pid, char *str)
{
	while (*str)
	{
		send_char(pid, *str);
		str++;
	}
	send_char(pid, '\0');
}

int	is_valid_pid(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
