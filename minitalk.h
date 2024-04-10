/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegendr <tlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 20:07:23 by tlegendr          #+#    #+#             */
/*   Updated: 2024/04/10 15:23:47 by tlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>

typedef struct s_message_buffer
{
	char		*msg;
	size_t		msg_size;
	size_t		msg_capacity;
}	t_message_buffer;

void	send_bit(int pid, int bit);
void	send_char(int pid, char c);
void	send_int(int pid, unsigned int n);
void	handler(int sig);

void	clear_msg(pid_t pid, int should_send);
void	handler_serv(int sig, siginfo_t *info, void *context);

int		ft_atoi(const char *string);
int		ft_strlen(char *msg);

#endif