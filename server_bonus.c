/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegendr <tlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 20:43:21 by tlegendr          #+#    #+#             */
/*   Updated: 2024/04/10 15:09:48 by tlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "ft_printf.h"

t_message_buffer	g_msg = {};

void	clear_msg(pid_t pid, int should_send)
{
	ft_printf("%s\n", g_msg.msg);
	free(g_msg.msg);
	g_msg.msg = NULL;
	g_msg.msg_size = 0;
	g_msg.msg_capacity = 0;
	if (should_send)
		kill(pid, SIGUSR2);
}

void	handler_serv(int sig, siginfo_t *info,
						void *context __attribute__((unused)))
{
	static unsigned int	i;
	static unsigned int	data;

	if (sig == SIGUSR1)
		data |= (1 << i);
	i++;
	if (g_msg.msg_capacity == 0)
	{
		if (i == 32)
		{
			g_msg.msg_capacity = data + 1;
			g_msg.msg = malloc(data + 1);
			data = 0;
			i = 0;
		}
	}
	else if (i == 8)
	{
		g_msg.msg[g_msg.msg_size++] = data;
		if (g_msg.msg_size == g_msg.msg_capacity)
			clear_msg(info->si_pid, 1);
		data = 0;
		i = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	s_sigaction;

	ft_printf("Server PID: %d\n", getpid());
	s_sigaction.sa_sigaction = handler_serv;
	s_sigaction.sa_flags = SA_SIGINFO;
	sigaction (SIGUSR1, &s_sigaction, NULL);
	sigaction (SIGUSR2, &s_sigaction, NULL);
	while (1)
		pause();
	free(g_msg.msg);
	return (0);
}
