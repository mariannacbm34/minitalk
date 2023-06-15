/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmonte <marmonte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:52:58 by marmonte          #+#    #+#             */
/*   Updated: 2023/06/15 16:46:05 by marmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	size_t	result;
	int		sinal;
	int		i;

	i = 0;
	sinal = 1;
	result = 0;
	while (str[i] && ((str[i] > 8 && str[i] < 14) || str[i] == 32))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sinal = -1;
		i++;
	}
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
		result = (result * 10) + str[i++] - 48;
	return (result * sinal);
}

int check_pid(char *pid)
{
	int i;

	i = 0;
	while (pid[i])
	{
		if (pid[i] < 48 || pid[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

void	send_signals(int pid, char byte)
{
	int	bit;
	
	bit = 0;
	while (bit < 8)
	{
		if (byte & 1)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				write(1, "Error: Couldn't send the message 🥺\n", 39);
				exit(0);
			}
		}
		else if (kill(pid, SIGUSR2) == -1)
		{
			write(1, "Error: Couldn't send the message 🥺\n", 39);
			exit(0);
		}
		bit++;
		byte >>= 1;
		usleep(700);
	}
}

int main(int argc, char **argv)
{
	int	i;
	
	i = 0;
	if (argc != 3)
	{
		write(1, "🌸 USAGE: ./client [PID] [MESSAGE] 🌸\n", 42);
		return (0);
	}
	if (check_pid(argv[1]))
	{
		write(1, "Error: Invalid PID 🥺\n", 25);
		return (0);
	}
	if (argc == 3)
	{
		write(1, "🌸 Sending message... 🌸\n", 30);
		while (argv[2][i])
			send_signals(ft_atoi(argv[1]), argv[2][i++]);
		write(1, "🌟 Message sent! 🌟\n", 25);
	}
	return (0);
}
