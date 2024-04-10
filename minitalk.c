/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlegendr <tlegendr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:52:53 by tlegendr          #+#    #+#             */
/*   Updated: 2024/04/10 15:01:30 by tlegendr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		i++;
	return (i);
}

int	ft_atoi(const char *string)
{
	int	i;
	int	result;
	int	is_negative;

	i = 0;
	result = 0;
	is_negative = 0;
	while (string[i] == ' ' || string[i] == '\t' || string[i] == '\n'
		|| string[i] == '\v' || string[i] == '\f' || string[i] == '\r')
		i++;
	if (string[i] == '-')
		is_negative = 1;
	if (string[i] == '-' || string[i] == '+')
		i++;
	while (string[i] >= '0' && string[i] <= '9')
	{
		result = result * 10 + (string[i] - '0');
		i++;
	}
	if (is_negative == 1)
		return (-result);
	return (result);
}
