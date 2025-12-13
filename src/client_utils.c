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

extern volatile sig_atomic_t	g_ack;

static int	send_bit(int pid, int bit)
{
	int	sig;

	g_ack = 0;
	if (bit == 0)
		sig = SIGUSR1;
	else
		sig = SIGUSR2;
	if (kill(pid, sig) == -1)
		return (-1);
	while (!g_ack)
		pause();
	return (0);
}

void	send_char(int pid, unsigned char c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if (send_bit(pid, (c >> bit) & 1) == -1)
		{
			ft_putstr_fd("Error: Failed to send signal\n", 2);
			exit(1);
		}
		bit--;
	}
}

void	send_string(int pid, char *str)
{
	while (*str)
	{
		send_char(pid, (unsigned char)*str);
		str++;
	}
	send_char(pid, '\0');
}

int	is_valid_pid(char *str)
{
	int		i;
	long	val;

	i = 0;
	val = 0;
	if (str[0] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		val = val * 10 + (str[i] - '0');
		if (val > 2147483647)
			return (0);
		i++;
	}
	return (1);
}
