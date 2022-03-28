/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alakhdar <<marvin@42.fr>>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 09:34:11 by alakhdar          #+#    #+#             */
/*   Updated: 2022/03/03 16:39:19 by alakhdar         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_data *args)
{
	free(args->tids);
	free(args->all_philos);
	free(args->forks);
}

// Dévérouille et détruit les mutex
void	destroy_mutex(t_data *args)
{
	int	nbr_ph;

	nbr_ph = args->nbr_philo;
	while (nbr_ph--)
	{
		pthread_mutex_unlock(&args->forks[nbr_ph]);
		pthread_mutex_destroy(&args->forks[nbr_ph]);
	}
	pthread_mutex_unlock(&(*args).lock_print);
	pthread_mutex_destroy(&(*args).lock_print);
}

void	end_threads(t_data *args)
{
	int	nbr_ph;

	nbr_ph = args->nbr_philo;
	if (nbr_ph == 1)
	{
		pthread_mutex_unlock(&args->forks[0]);
	}
	while (nbr_ph)
	{
		nbr_ph--;
		pthread_join(args->tids[nbr_ph], NULL);
	}
}

// Display un message d'erreur
void	error_exit(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(1, &msg[i], 1);
		i++;
	}
}
