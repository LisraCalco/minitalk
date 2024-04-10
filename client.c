/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegendr <tlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:43:14 by tlegendr          #+#    #+#             */
/*   Updated: 2024/04/10 15:14:42 by tlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "ft_printf.h"
#include <signal.h>

int	g_ack = 0;

void	send_bit(int pid, int bit)
{
	if (bit)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	while (!g_ack)
		usleep(10);
	g_ack = 0;
}

void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		send_bit(pid, c & 1);
		c >>= 1;
		i++;
	}
}

void	send_int(int pid, unsigned int n)
{
	int	i;

	i = 0;
	while (i < 32)
	{
		send_bit(pid, n & 1);
		n >>= 1;
		i++;
	}
}

void	handler(int sig)
{
	(void)sig;
	g_ack = 1;
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*msg;

	if (argc != 3)
	{
		ft_printf("Usage: %s [PID] [Message]\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0 || kill(pid, 0) == -1)
	{
		ft_printf("Invalid PID\n");
		return (1);
	}
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	msg = argv[2];
	send_int(pid, ft_strlen(msg));
	while (*msg)
	{
		send_char(pid, *msg);
		msg++;
	}
	send_char(pid, 0);
	return (0);
}
