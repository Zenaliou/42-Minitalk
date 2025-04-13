/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:44:42 by marvin            #+#    #+#             */
/*   Updated: 2025/02/28 09:44:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"

void	handle_signal(int sig, siginfo_t *info, void *context) // fonction qui permet de recevoir le signal (SIGUSR1 ou SIGUSR2)
{
	static int	bit = 0;
	static int	character = 0;

	(void)context;
	if (sig == SIGUSR1) // si le signal est SIGUSR1
		character |= (1 << (7 - bit)); // decaler le bit de 7-i vers la droite et mettre le bit a 1
	bit++;
	if (bit == 8) // si on a recu 8 bits (caractere complet)
	{
		write(1, &character, 1); // on affiche le caractere
		if (character == '\0')
			write(1, "\n", 1);
		bit = 0;
		character = 0;
		kill(info->si_pid, SIGUSR1); // on envoie un signal au client pour dire qu'on a bien recu le caractere (BONUS)
	}
}

int	main(void)
{
	struct sigaction	sa; // structure qui permet de gerer les signaux

	ft_printf("Server PID: %d\n", getpid());
	sa.sa_sigaction = handle_signal; // on dit a la structure de gerer le signal avec la fonction handle_signal
	sa.sa_flags = SA_SIGINFO; // on dit a la structure de gerer le signal avec les infos du signal
	sigemptyset(&sa.sa_mask); // on vide le masque de la structure
	sigaction(SIGUSR1, &sa, NULL); // on dit a la structure de gerer le signal SIGUSR1 avec la fonction handle_signal
	sigaction(SIGUSR2, &sa, NULL); // on dit a la structure de gerer le signal SIGUSR2 avec la fonction handle_signal
	while (1)
		pause();
	return (0);
}
