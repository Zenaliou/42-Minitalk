/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:44:39 by marvin            #+#    #+#             */
/*   Updated: 2025/02/28 09:44:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"

void	send_signal(int pid, char c) // fonction qui permet d'envoyer un signal (SIGUSR1 ou SIGUSR2)
{
	int	i;

	i = 0;
	while (i < 8) // parcourir les 8 bits du caractère 
	{
		if ((c >> (7 - i)) & 1) // decaler le bit de 7-i vers la droite et verifie si c'est un 1 ou un 0
			kill(pid, SIGUSR1); // si c'est un 1, on envoie SIGUSR1
		else
			kill(pid, SIGUSR2); // si c'est un 0, on envoie SIGUSR2
		usleep(100); // attendre 100 microsecondes entre chaque envoi sinon le serveur recoit pas correctement le signal
		i++;
	}
}

void	handle_ack(int sig) // fonction qui permet de dire au client que le serveur a bien recu le signal (BONUS)
{
	(void)sig;
	ft_printf("Recu\n");
}

int	main(int argc, char **argv)
{
	int		pid; // pid du serveur (server.c)
	int		i;

	if (argc != 3)
	{
		ft_printf("Usage: ./client <PID> <message>\n");
		return (1);
	}
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, handle_ack); // on dit au client de recevoir le signal SIGUSR1 (BONUS)
	i = 0;
	while (argv[2][i]) // tant que le message n'est pas fini
	{
		send_signal(pid, argv[2][i]); // on envoie le signal au serveur
		i++;
	}
	send_signal(pid, '\0'); // le null a la fin
	return (0);
}
