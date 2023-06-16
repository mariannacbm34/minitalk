/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marmonte <marmonte@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 15:52:55 by marmonte          #+#    #+#             */
/*   Updated: 2023/06/15 21:31:18 by marmonte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nbr)
{	
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr > 9)
	{
		ft_putnbr(nbr / 10);
		ft_putnbr(nbr % 10);
	}
	else if (nbr >= 0 && nbr <= 9)
		ft_putchar(nbr + 48);
}

char	math_power(unsigned char base, unsigned char power)
{
	unsigned char	result;

	result = 1;
	while (power > 0)
	{
		result = result * base;
		power--;
	}
	return (result);
}

void	read_signals(int bit)
{
	static unsigned int	power;
	static unsigned int	byte;
	
	if (bit == SIGUSR1)
		byte += math_power(2, power);
	power++;
	if (power == 8)
	{
		write(1, &byte, 1);
		power = 0;
		byte = 0;
	}
}

int	main(void)
{
	__pid_t				pid;
	struct sigaction	sigact;

	pid = getpid();
	write(1, "Server PID: ", 13);
	ft_putnbr(pid);
	ft_putchar('\n');
	write(1, "Waiting for signals...\n", 24);
	sigact.sa_flags = SA_RESTART;
	sigact.sa_handler = read_signals;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
}
