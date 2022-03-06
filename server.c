/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abigeddi <abigeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 00:41:27 by abigeddi          #+#    #+#             */
/*   Updated: 2022/03/06 18:02:10 by abigeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
