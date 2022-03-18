/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abigeddi <abigeddi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 17:31:54 by abigeddi          #+#    #+#             */
/*   Updated: 2022/03/18 23:10:07 by abigeddi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	send_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if (c >> i & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		i--;
		usleep(500);
	}
}

int	check_error(char *s)
{
	int	pid;
	int	i;

	pid = ft_atoi(s);
	if (pid < 0)
		return (0);
	i = kill(pid, 0);
	if (i == -1)
		return (0);
	return (pid);
}

void	msg(int sig)
{
	if (sig == SIGUSR1)
		ft_putstr("message recu\n");
}

int	main(int ac, char **av)
{
	int		pid;
	char	*s;
	int		i;

	i = 0;
	if (ac == 3)
	{
		pid = check_error(av[1]);
		if (pid > 0)
		{
			s = av[2];
			signal(SIGUSR1, msg);
			while (s[i])
			{
				send_char(pid, s[i]);
				i++;
			}
			send_char(pid, 0);
		}
		else
			ft_putstr("incorrect pid\n");
	}
	else
		ft_putstr("syntax error!\n");
	return (0);
}
