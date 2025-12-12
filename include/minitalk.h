/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by student           #+#    #+#             */
/*   Updated: 2025/12/12 00:00:00 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

/* Utils function prototypes */
int		ft_atoi(const char *str);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putnbr(int n);

/* Client function prototypes */
void	send_bit(int pid, int bit);
void	send_char(int pid, char c);
void	send_string(int pid, char *str);
int		is_valid_pid(char *str);

#endif

