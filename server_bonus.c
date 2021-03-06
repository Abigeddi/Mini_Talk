/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abigeddi <abigeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:32:06 by abigeddi          #+#    #+#             */
/*   Updated: 2022/03/18 23:12:24 by abigeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include <stdio.h>

int	g_pid = 0;

void	handler(int signum, siginfo_t *sig_info, void *context)
{
	static char	ascii;
	static int	i;

	(void) context;
	signum -= SIGUSR1;
	if (g_pid != sig_info->si_pid)
	{
		ascii = 0;
		i = 0;
		g_pid = sig_info->si_pid;
	}
	if (signum)
		ascii = ascii << 1 | 1;
	if (!signum)
		ascii = ascii << 1 | 0;
	i++;
	if (i == 8)
	{
		if (ascii == '\0')
			kill (g_pid, SIGUSR1);
		ft_putchar(ascii);
		i = 0;
		ascii = 0;
	}
}

int	main(void)
{
	struct sigaction	sig;

	sig.sa_sigaction = &handler;
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	ft_putstr("PID = ");
	ft_putnbr(getpid());
	ft_putstr("\n");
	while (1)
		pause();
}
